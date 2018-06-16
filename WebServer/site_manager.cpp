/*
Copyright 2018 Jesse Laning
*/

#include "site_manager.h"

using webserver::ServerConfig;
using webserver::site::Site;
using webserver::site::SiteManager;

SiteManager::SiteManager(const std::shared_ptr<ServerConfig>& serverConfig)
    : serverConfig(serverConfig) {
  std::filesystem::path path((*serverConfig)["sites"]);
  if (path.is_relative()) path = serverConfig->getParent() / path;
  if (std::filesystem::exists(path))
    for (auto& di : std::filesystem::directory_iterator(path))
      if (!std::filesystem::is_directory(di.path())) load(di.path().string());
}

void SiteManager::load(const std::filesystem::path& path) {
  std::shared_ptr<Site> ptr = std::make_shared<Site>(path, serverConfig);
  auto pairib = sites.insert({ptr->getName(), std::move(ptr)});
  if (pairib.second)
    if (pairib.first->second->isDefault()) defaultSite = pairib.first->second;
}

const Site& SiteManager::get(const std::string& name) const {
  if (sites.find(name) != sites.end()) return *sites.find(name)->second;
  return getDefault();
}

const Site& SiteManager::operator[](const std::string& name) const {
  if (sites.find(name) != sites.end()) return *sites.find(name)->second;
  return getDefault();
}

const std::vector<std::shared_ptr<Site>> SiteManager::operator*() const {
  std::vector<std::shared_ptr<Site>> r;
  r.reserve(sites.size());
  for (auto it = sites.begin(); it != sites.end(); ++it)
    r.push_back(it->second);
  return r;
}

const Site& SiteManager::getDefault() const {
  if (defaultSite == nullptr) return *sites.begin()->second;
  return *defaultSite;
}
