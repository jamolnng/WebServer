/*
Copyright 2018 Jesse Laning
*/

#include "file_utils.h"
#include "plugin_manager.h"

using webserver::plugin::Plugin;
using webserver::plugin::PluginManager;

typedef Plugin*(__stdcall* CreatePlugin)();

PluginManager::PluginManager(const webserver::Config& conf) : config(conf) {
  std::filesystem::path path(config["plugins"]);
  if (path.is_relative()) path = config.getParent() / path;
  if (std::filesystem::exists(path))
    for (auto& di : std::filesystem::directory_iterator(path))
      if (std::filesystem::is_directory(di.path()))
        if (std::filesystem::exists(di.path() / "plugin.cfg"))
          load(di.path().filename().generic_string());
}

PluginManager::~PluginManager() {
  for (auto& plugin : plugins) utils::LibUtils::dlclose(plugin.second.first);
}

void PluginManager::load(const std::string& name) {
  std::filesystem::path p(config["plugins"]);
  p /= name;
  p /= name + utils::LibUtils::libExt;
  std::string libPath = p.generic_string();
  auto lib = utils::LibUtils::dlopen(libPath, RTLD_LAZY);
  if (!lib) {
    // std::cout << utils::LibUtils::dlerror() << std::endl;
    return;
  }
  CreatePlugin create =
      (CreatePlugin)utils::LibUtils::dlsym(lib, "CreatePlugin");
  if (!create) {
    // std::cout << utils::LibUtils::dlerror() << std::endl;
    utils::LibUtils::dlclose(lib);
    return;
  }
  plugins[name] = {lib, create()};
}

bool PluginManager::has(const std::string& name) {
  return plugins.find(name) != plugins.end();
}

Plugin& PluginManager::get(const std::string& name) {
  return *(plugins[name].second);
}

Plugin& PluginManager::operator[](const std::string& name) { return get(name); }

std::vector<Plugin*> PluginManager::operator*() {
  std::vector<Plugin*> r;
  r.reserve(plugins.size());
  for (auto it = plugins.begin(); it != plugins.end(); ++it)
    r.push_back(it->second.second);
  return r;
}
