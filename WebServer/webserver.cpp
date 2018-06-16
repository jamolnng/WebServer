/*
Copyright 2018 Jesse Laning
*/

#include "webserver.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "error.h"
#include "logger.h"
#include "request_parser.h"
#include "response.h"
#include "site.h"
#include "status_code.h"
#include "string_utils.h"
#include "win_utils.h"
#include "ws_version.h"

using std::chrono::system_clock;
using webserver::ServerConfig;
using webserver::WebServer;
using webserver::http::error::Error;
using webserver::http::request::Request;
using webserver::http::request::RequestParser;
using webserver::http::response::Response;
using webserver::http::response::StatusCode;
using webserver::plugin::Plugin;
using webserver::plugin::PluginManager;
using webserver::site::SiteManager;
using webserver::utils::Logger;
using webserver::utils::MimeTypes;
using webserver::utils::SocketUtils;
using webserver::utils::StringUtils;

Logger& logger = webserver::utils::Logger::instance();

WebServer::WebServer(const std::shared_ptr<ServerConfig>& serverConfig)
    : serverConfig(serverConfig),
      pluginManager(PluginManager(serverConfig)),
      siteManager(SiteManager(serverConfig)),
      port(serverConfig->get<int>("port")) {
  if (SocketUtils::init() != 0)
    throw std::runtime_error("Failed to initialize WinSock");
  if ((*siteManager).empty()) throw std::runtime_error("No sites loaded");
}

WebServer::~WebServer() { SocketUtils::quit(); }

void WebServer::start() {
  if (running) {
    logger.error("Server already running");
    return;
  }

  std::shared_ptr<addrinfo> res(nullptr,
                                [](addrinfo* ai) { freeaddrinfo(ai); });
  addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;

  if (getaddrinfo(NULL, std::to_string(port).c_str(), &hints,
                  reinterpret_cast<addrinfo**>(&res)) != 0)
    throw std::runtime_error("Failed to get address info");

  server = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (server == INVALID_SOCKET)
    throw std::runtime_error("Failed to create socket");

#ifdef _WIN32
  DWORD timeout = serverConfig->get<int>("timeout") * 1000;
  if (setsockopt(server, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout,
                 sizeof timeout) == SOCKET_ERROR) {
    SocketUtils::close(server);
    throw std::runtime_error("Failed to set recv timeout");
  }
#else
  struct timeval tv;
  tv.tv_sec = serverConfig->get<int>("timeout");
  tv.tv_usec = 0;
  if (setsockopt(server, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv,
                 sizeof tv)) {
    SocketUtils::close(server);
    throw std::runtime_error("Failed to set recv timeout");
  }
#endif

  if (bind(server, res->ai_addr, static_cast<int>(res->ai_addrlen)) ==
      SOCKET_ERROR) {
    SocketUtils::close(server);
    throw std::runtime_error("Failed to bind socket");
  }

  if (listen(server, SOMAXCONN) == SOCKET_ERROR) {
    SocketUtils::close(server);
    throw std::runtime_error("Failed to start listening");
  }

  running = true;
  thread = std::thread([&](WebServer* server) { server->run(); }, this);
}

void WebServer::stop() {
  if (!running) {
    logger.error("Server not running");
    return;
  }
  running = false;
  for (std::pair<const SOCKET, std::thread>& a : clientThreads) {
    SocketUtils::shutdown(a.first);
    SocketUtils::close(a.first);
    if (a.second.joinable()) a.second.join();
  }
  SocketUtils::shutdown(server);
  SocketUtils::close(server);
  if (thread.joinable()) thread.join();
}

void WebServer::run() {
  SOCKET client;
  while (running) {
    client = accept(server, NULL, NULL);
    if (client == INVALID_SOCKET) {
      if (running)
        logger.error("Error accepting client connection: " +
                     StringUtils::strerror(errno));
      continue;
    } else {
      if (clientThreads.find(client) != clientThreads.end()) {
        if (clientThreads[client].joinable()) clientThreads[client].join();
        clientThreads.erase(client);
      }
      clientThreads[client] = std::thread(
          [&](WebServer* w) {
            w->handleClient(client, 256, serverConfig->get<int>("timeout"));
          },
          this);
    }
  }
}

void WebServer::handleClient(SOCKET client, int bufferSize, int timeout) const {
  RequestParser parser;
  Request request;
  Response response;
  site::Site site = siteManager.getDefault();
  std::vector<std::shared_ptr<Plugin>> plugins = *pluginManager;
  std::vector<char> buffer(bufferSize, 0);
  std::string responseMessage;

  fd_set set;
  struct timeval tv;
  FD_ZERO(&set);
  FD_SET(client, &set);
  tv.tv_sec = timeout;
  tv.tv_usec = 0;

  int status;
  int bytes;

  sockaddr_in clientInfo;
  socklen_t addrLen = sizeof(clientInfo);
  std::string clientIP;
  if (getpeername(client, (sockaddr*)&clientInfo, &addrLen) == SOCKET_ERROR) {
    logger.error("Error getting client IP: " + StringUtils::strerror(errno));
    goto close;
  }
  clientIP = std::string(inet_ntoa(clientInfo.sin_addr));

  logger.info("Accepted connection from: " + clientIP);

  while (true) {
    response.clear();
    while (!parser) {
      status = select(FD_SETSIZE, &set, NULL, NULL, &tv);
      if (status == SOCKET_ERROR) {
        if (running)
          logger.error("Socket error selecting client (" + clientIP +
                       "): " + StringUtils::strerror(errno));
        goto close;
      } else if (status == 0) {
        logger.info("Client timed out (" + clientIP + ")");
        goto close;
      } else {
        bytes = recv(client, &buffer[0], static_cast<int>(buffer.size()), NULL);
        if (bytes == SOCKET_ERROR) {
          if (running)
            logger.error("Socket error on recv (" + clientIP +
                         "): " + StringUtils::strerror(errno));
          goto close;
        } else if (bytes == 0) {
          logger.info("Peer disconnect (" + clientIP + ")");
          goto close;
        } else {
          parser << std::string(&buffer[0], bytes);
        }
      }
    }
    request = parser.get();
    const http::message::GeneralHeader& reqGeneral = request.getGeneralHeader();
    const http::request::RequestHeader reqHead = request.getRequestHeader();
    http::response::StatusLine& statLine = response.getStatusLine();
    http::response::ResponseHeader& resHead = response.getResponseHeader();
    http::entity::EntityHeader& resEntity = response.getEntityHeader();
    http::message::GeneralHeader& resGeneral = response.getGeneralHeader();

    for (auto p : plugins)
      if (p->modifyRequest(request)) break;

    if (reqGeneral.has("Connection") && reqGeneral["Connection"] == "close")
      goto close;

    if (reqHead.has("Host"))
      site = siteManager[reqHead["Host"]];
    else
      site = siteManager.getDefault();
    statLine["HTTP-Version"] = "HTTP/1.1";
    statLine["Status-Code"] = std::to_string(StatusCode::OK);
    statLine["Reason-Phrase"] = StatusCode::getString(StatusCode::OK);
    resGeneral["Connection"] = reqGeneral["Connection"];

    try {
      responseMessage = site.getMessage(request, response, plugins);
    } catch (const Error& messageError) {
      statLine["Status-Code"] = std::to_string(messageError.code());
      statLine["Reason-Phrase"] = messageError.what();
      try {
        responseMessage =
            site.getErrorMessage(messageError, request, response, plugins);
      } catch (const Error&) {
        responseMessage =
            site.getDefaultErrorMessage(messageError, request, response);
      } catch (const std::exception& e) {
        responseMessage = e.what();
      }
    } catch (const std::exception& e) {
      responseMessage = e.what();
    }
    if (!resEntity.has("Content-Type"))
      resEntity["Content-Type"] = "*/*;charset=UTF-8";
    resEntity["Content-Length"] = std::to_string(responseMessage.size());

    auto now_c = system_clock::to_time_t(system_clock::now());
    std::stringstream date;
    date << std::put_time(std::gmtime(&now_c), "%a, %e %b %Y %T GMT");
    resGeneral["Date"] = date.str();

    resHead["Server"] = WS_VER_PRETTY;

    std::string http = response.build() + responseMessage;
    send(client, http.c_str(), static_cast<int>(http.size()), 0);
  }
close:
  SocketUtils::shutdown(client);
  SocketUtils::close(client);
  logger.info("Connection closed (" + clientIP + ")");
}

const bool WebServer::isRunning() const { return running; }
