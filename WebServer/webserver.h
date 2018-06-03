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
		static void handleClient(SOCKET client, int buffer_size, int timeout);

		std::thread thread;
		std::atomic<bool> running{ false };
		SOCKET server;
		std::map<SOCKET, std::thread> clientThreads;
		int port;
		config::Config& config;
		plugin::PluginManager pluginManager;
	};
}