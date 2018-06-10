/*
Copyright 2018 Jesse Laning
*/

#include <iostream>
#include <memory>
#include "file_utils.h"
#include "plugin_manager.h"

using webserver::ServerConfig;
using webserver::plugin::Plugin;
using webserver::plugin::PluginManager;

typedef Plugin*(__stdcall* CreatePlugin)(const std::shared_ptr<ServerConfig>&);

PluginManager::PluginManager(const std::shared_ptr<ServerConfig>& serverConfig)
    : serverConfig(serverConfig),
      pluginDir(serverConfig->operator[]("plugins")) {
  if (pluginDir.is_relative())
    pluginDir = serverConfig->getParent() / pluginDir;
  if (std::filesystem::exists(pluginDir))
    for (auto& di : std::filesystem::directory_iterator(pluginDir))
      if (std::filesystem::is_directory(di.path()))
        if (std::filesystem::exists(di.path() / "plugin.cfg"))
          load(di.path().filename().string());
}

PluginManager::~PluginManager() {
  for (auto& plugin : plugins) utils::LibUtils::dlclose(plugin.second.first);
}

void PluginManager::load(const std::string& name) {
  std::filesystem::path p = pluginDir / name / (name + utils::LibUtils::libExt);
  std::string libPath = p.string();
  auto lib = utils::LibUtils::dlopen(libPath, RTLD_LAZY);
  if (!lib) {
    // std::cout << utils::LibUtils::dlerror() << std::endl;
    return;
  }
  CreatePlugin create = reinterpret_cast<CreatePlugin>(
      utils::LibUtils::dlsym(lib, "CreatePlugin"));
  if (!create) {
    // std::cout << utils::LibUtils::dlerror() << std::endl;
    utils::LibUtils::dlclose(lib);
    return;
  }
  plugins[name] = {lib, std::shared_ptr<Plugin>(create(serverConfig))};
}

bool PluginManager::has(const std::string& name) {
  return plugins.find(name) != plugins.end();
}

Plugin& PluginManager::get(const std::string& name) {
  return *(plugins[name].second);
}

Plugin& PluginManager::operator[](const std::string& name) { return get(name); }

std::vector<std::shared_ptr<Plugin>> PluginManager::operator*() {
  std::vector<std::shared_ptr<Plugin>> r;
  r.reserve(plugins.size());
  for (auto it = plugins.begin(); it != plugins.end(); ++it)
    r.push_back(it->second.second);
  return r;
}
