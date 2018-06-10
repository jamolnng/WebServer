/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "file_utils.h"
#include "lib_utils.h"
#include "plugin.h"
#include "server_config.h"

namespace webserver {
namespace plugin {
class PluginManager {
 public:
  explicit PluginManager(const std::shared_ptr<ServerConfig>& serverConfig);
  ~PluginManager();

  void load(const std::string& name);
  bool has(const std::string& name);
  Plugin& get(const std::string& name);
  Plugin& operator[](const std::string& item);
  std::vector<std::shared_ptr<Plugin>> operator*();

 private:
  std::map<std::string,
           std::pair<utils::LibUtils::LIBHANDLE, std::shared_ptr<Plugin>>>
      plugins;
  std::shared_ptr<ServerConfig> serverConfig;
  std::filesystem::path pluginDir;
};
}  // namespace plugin
}  // namespace webserver
