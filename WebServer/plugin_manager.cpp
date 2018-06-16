/*
Copyright 2018 Jesse Laning
*/

#include <memory>
#include "file_utils.h"
#include "plugin_manager.h"

using webserver::ServerConfig;
using webserver::plugin::Plugin;
using webserver::plugin::PluginManager;
using webserver::utils::LibUtils;
namespace fs = std::filesystem;

typedef Plugin*(__stdcall* CreatePlugin)(const std::shared_ptr<ServerConfig>&);

PluginManager::PluginManager(const std::shared_ptr<ServerConfig>& serverConfig)
    : serverConfig(serverConfig), pluginDir((*serverConfig)["plugins"]) {
  if (pluginDir.is_relative())
    pluginDir = serverConfig->getParent() / pluginDir;
  if (fs::exists(pluginDir))
    for (auto& di : fs::directory_iterator(pluginDir))
      if (fs::is_directory(di.path()))
        if (fs::exists(di.path() / "plugin.cfg"))
          load(di.path().filename().string());
}

PluginManager::~PluginManager() {
  for (auto& plugin : plugins) LibUtils::dlclose(plugin.second.first);
}

void PluginManager::load(const std::string& name) {
  fs::path p = pluginDir / name / (name + LibUtils::libExt);
  std::string libPath = p.string();
  auto lib = LibUtils::dlopen(libPath, RTLD_LAZY);
  if (!lib) {
    // std::cout << LibUtils::dlerror() << std::endl;
    return;
  }
  CreatePlugin create = reinterpret_cast<CreatePlugin>(
      LibUtils::dlsym(lib, "CreatePlugin"));
  if (!create) {
    // std::cout << LibUtils::dlerror() << std::endl;
    LibUtils::dlclose(lib);
    return;
  }
  plugins[name] = {lib, std::shared_ptr<Plugin>(create(serverConfig))};
}

bool PluginManager::has(const std::string& name) const {
  return plugins.find(name) != plugins.end();
}

const Plugin& PluginManager::get(const std::string& name) const {
  return *(plugins.at(name).second);
}

const Plugin& PluginManager::operator[](const std::string& name) const { return get(name); }

std::vector<std::shared_ptr<Plugin>> PluginManager::operator*() const {
  std::vector<std::shared_ptr<Plugin>> r;
  r.reserve(plugins.size());
  for (auto it = plugins.begin(); it != plugins.end(); ++it)
    r.push_back(it->second.second);
  return r;
}
