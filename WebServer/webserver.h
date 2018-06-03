#pragma once
#include <atomic>
#include <map>
#include <thread>
#include "sock_utils.h"
#include "config.h"
#include "plugin_manager.h"

namespace webserver
{
	class WebServer
	{
	public:
		WebServer(config::Config& config);
		~WebServer();

		void start();
		void stop();

		bool isRunning();

	private:
		void run();
		void handle_client(SOCKET client);

		std::thread thread;
		std::atomic<bool> running{ false };
		SOCKET server;
		std::map<SOCKET, std::thread> client_threads;
		int port;
		const config::Config& config;
		plugin::PluginManager pluginManager;
	};
}