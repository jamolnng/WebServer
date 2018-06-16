/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <atomic>
#include <map>
#include <memory>
#include <thread>

#include "sock_utils.h"

#include "plugin_manager.h"
#include "server_config.h"
#include "site_manager.h"

namespace webserver {
class WebServer {
 public:
  explicit WebServer(const std::shared_ptr<ServerConfig>& serverConfig);
  ~WebServer();

  void start();
  void stop();

  const bool isRunning() const;

 private:
  void run();
  void handleClient(SOCKET client, int buffer_size, int timeout) const;

  std::thread thread;
  std::atomic<bool> running{false};
  SOCKET server{0};
  std::map<SOCKET, std::thread> clientThreads;
  int port;
  std::shared_ptr<ServerConfig> serverConfig;
  plugin::PluginManager pluginManager;
  site::SiteManager siteManager;
};
}  // namespace webserver
