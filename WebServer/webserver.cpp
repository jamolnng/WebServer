#include "webserver.h"
#include <string>
#include <iostream>

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
	int quit = SocketUtils::quit();
	if (quit != 0)
		throw std::runtime_error("Failed to shutdown WinSock");
}

void WebServer::start()
{
	if (running) return;

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
	if (!running) return;
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
			clientThreads[client] = std::thread(WebServer::handleClient, client, 256);
		}
	}
}

void WebServer::handleClient(SOCKET client, int bufferSize)
{
	std::string http = \
		"HTTP/1.1 200 OK\r\n"
		"Connection: close\r\n"
		"Content-type: text/html\r\n\r\n"
		"<!DOCTYPE html>\r\n"
		"<html>\r\n"
		"<head>\r\n"
		"<title>Hello, World!</title>\r\n"
		"</head>\r\n"
		"<body>\r\n"
		"Hello, World!\r\n"
		"</body>\r\n"
		"</html>\r\n";


	sockaddr_in clientInfo;
	socklen_t addrLen = sizeof(clientInfo);
	int status;
	status = getpeername(client, (sockaddr*)&clientInfo, &addrLen);
	if (status != 0)
	{
		SocketUtils::shutdown(client);
		SocketUtils::close(client);
		return;
	}
	char* clientIP = inet_ntoa(clientInfo.sin_addr);

	std::vector<char> buffer(bufferSize, 0);
	std::string s;
	int toRecv;
	do
	{
		SocketUtils::ioctl(client, FIONREAD, &toRecv);
		if (toRecv)
		{
			std::fill(buffer.begin(), buffer.end(), 0);
			int bytes = recv(client, &buffer[0], (int)buffer.size(), NULL);
			if (bytes > 0)
			{
				s += std::string(buffer.begin(), buffer.begin() + bytes);
			}
			else
			{
				SocketUtils::shutdown(client);
				SocketUtils::close(client);
				return;
			}
		}
	} while (toRecv);
	std::cout << s << std::endl;
	send(client, http.c_str(), http.size(), 0);
	SocketUtils::shutdown(client);
	SocketUtils::close(client);
}

bool WebServer::isRunning()
{
	return running;
}