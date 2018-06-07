#include "webserver.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include "request_parser.h"
#include "response.h"
#include "status_code.h"

using namespace webserver;
using webserver::utils::SocketUtils;
using webserver::http::response::StatusCode;

WebServer::WebServer(config::Config& config) :
	config(config),
	pluginManager(plugin::PluginManager(config)),
	port(config.get<int>("port")),
	server(SOCKET())
{
	if (SocketUtils::init() != 0)
		throw std::runtime_error("Failed to initialize WinSock");
}


WebServer::~WebServer()
{
	SocketUtils::quit();
}

void WebServer::start()
{
	if (running)
		return;

	std::shared_ptr<addrinfo> res(nullptr, [](addrinfo* ai) { freeaddrinfo(ai); });
	addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, std::to_string(port).c_str(), &hints, (addrinfo**)&res) != 0)
		throw std::runtime_error("Failed to get address info");

	server = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (server == INVALID_SOCKET)
		throw std::runtime_error("Failed to create socket");

	if (bind(server, res->ai_addr, (int)res->ai_addrlen) == SOCKET_ERROR)
	{
		SocketUtils::close(server);
		throw std::runtime_error("Failed to bind socket");
	}

	if (listen(server, SOMAXCONN) == SOCKET_ERROR)
	{
		SocketUtils::close(server);
		throw std::runtime_error("Failed to start listening");
	}

	running = true;
	thread = std::thread([&](WebServer* server) { server->run(); }, this);
}

void WebServer::stop()
{
	for (std::pair<const SOCKET, std::thread> &a : clientThreads)
	{
		SocketUtils::shutdown(a.first);
		SocketUtils::close(a.first);
		if (a.second.joinable())
			a.second.join();
	}
	SocketUtils::shutdown(server);
	SocketUtils::close(server);
	if (!running)
		return;
	running = false;
	if (thread.joinable())
		thread.join();
}

void WebServer::run()
{
	SOCKET client;
	while (running)
	{
		client = accept(server, NULL, NULL);
		if (client == INVALID_SOCKET) // error
			continue;
		else
		{
			if (clientThreads.count(client))
			{
				SocketUtils::shutdown(client);
				SocketUtils::close(client);
				if (clientThreads[client].joinable())
					clientThreads[client].join();
			}
			clientThreads[client] = std::thread(WebServer::handleClient, client, 256, config.get<int>("timeout"));
		}
	}
}

void WebServer::handleClient(SOCKET client, int bufferSize, int timeout)
{
	http::request::RequestParser parser;
	http::request::Request request;
	http::response::Response response;
	std::vector<char> buffer(bufferSize, 0);

	/*sockaddr_in clientInfo;
	socklen_t addrLen = sizeof(clientInfo);
	char* clientIP;
	
	if (getpeername(client, (sockaddr*)&clientInfo, &addrLen) != 0)
		goto close;
	clientIP = inet_ntoa(clientInfo.sin_addr);*/

	fd_set set;
	struct timeval tv;
	FD_ZERO(&set);
	FD_SET(client, &set);
	tv.tv_sec = 5;
	tv.tv_usec = 0;

	int status;
	int bytes;

	
	while (true)
	{
		parser.clear();
		response.clear();
		while (!parser.isDone())
		{
			std::fill(buffer.begin(), buffer.end(), 0);
			status = select((int)client, &set, NULL, NULL, &tv);
			if (status == SOCKET_ERROR) // error
				goto close;
			else if (status == 0) // timeout
				goto close;
			else
			{
				bytes = recv(client, &buffer[0], (int)buffer.size(), NULL);
				if (bytes == SOCKET_ERROR) // error
					goto close;
				else if (bytes == 0) // peer disconnect
					goto close;
				else
					parser.parse(std::string(&buffer[0], bytes));
			}
		}
		request = parser.get();
		if (request.generalHeader.has("Connection") &&
			request.generalHeader["Connection"] == "close")
			goto close;

		std::string br = "<br/>";
		std::ostringstream content;
		content << "<!DOCTYPE html>" << std::endl;
		content << "<html>" << std::endl;
		content << "<head>" << std::endl;
		content << "<title>Hello, World!</title>" << std::endl;
		content << "</head>" << std::endl;
		content << "<body>" << std::endl;
		content << request.requestLine["Method"]
	     << " " << request.requestLine["Request-URI"]
		 << " " << request.requestLine["HTTP-Version"]
		 << br << std::endl;
		for (auto& a : *request.generalHeader)
			content << a.first << ": " << a.second << br << std::endl;
		for (auto& a : *request.requestHeader)
			content << a.first << ": " << a.second << br << std::endl;
		for (auto& a : *request.entityHeader)
			content << a.first << ": " << a.second << br << std::endl;
		content << "</body>" << std::endl;
		content << "</html>" << std::endl;

		response.statusLine["HTTP-Version"] = request.requestLine["HTTP-Version"];
		response.statusLine["Status-Code"] = StatusCode::OK;
		response.statusLine["Reason-Phrase"] = StatusCode::getString(StatusCode::OK);

		response.generalHeader["Connection"] = request.generalHeader["Connection"];
		
		response.entityHeader["Content-Type"] = "text/html";
		response.entityHeader["Content-Length"] = std::to_string(content.str().size());

		std::string http_header = response.build();
		std::string http = http_header + content.str();

		send(client, http.c_str(), (int)http.size(), 0);
	}
close:
	SocketUtils::shutdown(client);
	SocketUtils::close(client);
}

bool WebServer::isRunning()
{
	return running;
}