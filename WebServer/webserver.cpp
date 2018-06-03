#include "webserver.h"
#include <algorithm>
#include <iostream>
#include <string>
#include "request_parser.h"

using namespace webserver;
using webserver::utils::SocketUtils;

WebServer::WebServer(config::Config& config) :
	config(config),
	pluginManager(plugin::PluginManager(config)),
	port(config.getInt("port"))
{
	int init = SocketUtils::init();
	if (init != 0)
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

	int status;
	status = getaddrinfo(NULL, std::to_string(port).c_str(), &hints, (addrinfo**)&res);
	if (status != 0)
		throw std::runtime_error("Failed to get address info");

	server = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (server == INVALID_SOCKET)
		throw std::runtime_error("Failed to create socket");

	status = bind(server, res->ai_addr, (int)res->ai_addrlen);
	if (status == SOCKET_ERROR)
	{
		SocketUtils::close(server);
		throw std::runtime_error("Failed to bind socket");
	}

	status = listen(server, SOMAXCONN);
	if (status == SOCKET_ERROR)
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
		if (client != INVALID_SOCKET)
		{
			if (clientThreads.count(client))
			{
				SocketUtils::shutdown(client);
				SocketUtils::close(client);
				if (clientThreads[client].joinable())
					clientThreads[client].join();
			}
			clientThreads[client] = std::thread(WebServer::handleClient,
												client,
												256,
												config.getInt("timeout"));
		}
	}
}

void WebServer::handleClient(SOCKET client, int bufferSize, int timeout)
{
	std::string http_content = \
		"<!DOCTYPE html>\r\n"
		"<html>\r\n"
		"<head>\r\n"
		"<title>Hello, World!</title>\r\n"
		"</head>\r\n"
		"<body>\r\n"
		"Hello, World!\r\n"
		"</body>\r\n"
		"</html>\r\n";

	std::string http_header = \
		"HTTP/1.1 200 OK\r\n"
		"Connection: keep-alive\r\n"
		"Content-type: text/html\r\n"
		"Content-length: " + std::to_string(http_content.size()) + "\r\n"
		"\r\n";

	http::request::RequestParser parser;
	http::request::Request request;
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
		while (!parser.isDone())
		{
			std::fill(buffer.begin(), buffer.end(), 0);
			status = select(client, &set, 0, 0, &tv);
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
		if (request.generalHeader.connection.empty() ||
			request.generalHeader.connection == "close")
			goto close;
		std::string http = http_header + http_content;
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