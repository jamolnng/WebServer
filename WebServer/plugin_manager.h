/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "config.h"
#include "file_utils.h"
#include "lib_utils.h"
#include "plugin.h"

namespace webserver {
namespace plugin {
class PluginManager {
 public:
  explicit PluginManager(const webserver::Config& config);
  ~PluginManager();

  void load(const std::string& name);
  bool has(const std::string& name);
  Plugin& get(const std::string& name);
  Plugin& operator[](const std::string& item);
  std::vector<Plugin*> operator*();

 private:
  std::map<std::string, std::pair<utils::LibUtils::LIBHANDLE, Plugin*>> plugins;
  webserver::Config config;
};
}  // namespace plugin
}  // namespace webserver
