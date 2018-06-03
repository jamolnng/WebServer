#include "webserver.h"
#include <string>
#include <iostream>

using namespace webserver;
using webserver::utils::SocketUtils;

WebServer::WebServer(config::Config& config) :
	config(config),
	pluginManager(plugin::PluginManager(config))
{
	SocketUtils::init();
	port = config.getInt("port");
}


WebServer::~WebServer()
{
	SocketUtils::quit();
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

	getaddrinfo(NULL, std::to_string(port).c_str(), &hints, (addrinfo**)&res);

	server = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	bind(server, res->ai_addr, (int)res->ai_addrlen);
	listen(server, SOMAXCONN);

	running = true;
	thread = std::thread([&](WebServer* server) { server->run(); }, this);
}

void WebServer::stop()
{
	for (std::pair<const SOCKET, std::thread> &a : client_threads)
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
	while (running)
	{
		SOCKET client;
		client = accept(server, NULL, NULL);
		if (client != INVALID_SOCKET)
		{
			if (client_threads.count(client))
			{
				SocketUtils::shutdown(client);
				SocketUtils::close(client);
				if (client_threads[client].joinable())
					client_threads[client].join();
			}
			client_threads[client] = std::thread([&](WebServer* service) { service->handle_client(client); }, this);
		}
	}
}

void WebServer::handle_client(SOCKET client)
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
	int buffer_size = 256;
	std::vector<char> buffer(buffer_size, 0);
	std::string s;
	int toRecv;
	do
	{
		SocketUtils::ioctl(client, FIONREAD, &toRecv);
		if (toRecv)
		{
			std::fill(buffer.begin(), buffer.end(), 0);
			int bytes = recv(client, &buffer[0], (int)buffer.size(), NULL);
			s += std::string(buffer.begin(), buffer.begin() + bytes);
		}
	} while (toRecv);
	send(client, http.c_str(), http.size(), 0);
	SocketUtils::shutdown(client);
	SocketUtils::close(client);
}

bool WebServer::isRunning()
{
	return running;
}