/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <atomic>
#include <map>
#include <memory>
#include <thread>

#include "sock_utils.h"

#include "config_map.h"
#include "mime_types.h"
#include "plugin_manager.h"
#include "site_manager.h"

namespace webserver {
class WebServer {
 public:
  explicit WebServer(const StrStrConfig<>& config);
  ~WebServer();

  void start();
  void stop();

  bool isRunning();

 private:
  void run();
  void handleClient(SOCKET client, int buffer_size, int timeout);

  std::thread thread;
  std::atomic<bool> running{false};
  SOCKET server{0};
  std::map<SOCKET, std::thread> clientThreads;
  int port;
  StrStrConfig<> config;
  plugin::PluginManager pluginManager;
  site::SiteManager siteManager;
  utils::MimeTypes mimeTypes;
};
}  // namespace webserver
