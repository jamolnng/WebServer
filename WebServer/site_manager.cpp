/*
Copyright 2018 Jesse Laning
*/

#include "site_manager.h"

using webserver::StrStrConfig;
using webserver::site::Site;
using webserver::site::SiteManager;
using webserver::utils::MimeTypes;

SiteManager::SiteManager(const StrStrConfig<>& conf, MimeTypes* mimeTypes)
    : config(conf), mimeTypes(mimeTypes) {
  std::filesystem::path path(config["sites"]);
  if (path.is_relative()) path = config.getParent() / path;
  if (std::filesystem::exists(path))
    for (auto& di : std::filesystem::directory_iterator(path))
      if (!std::filesystem::is_directory(di.path()))
        load(di.path().generic_string());
}

void SiteManager::load(const std::filesystem::path& path) {
  std::shared_ptr<Site> ptr = std::make_shared<Site>(path, mimeTypes);
  auto pairib = sites.insert({ptr->getName(), std::move(ptr)});
  if (pairib.second)
    if (pairib.first->second->isDefault()) defaultSite = pairib.first->second;
}

Site& SiteManager::get(const std::string& name) {
  if (sites.find(name) != sites.end()) return *sites.find(name)->second;
  return getDefault();
}

Site& SiteManager::operator[](const std::string& name) {
  if (sites.find(name) != sites.end()) return *sites.find(name)->second;
  return getDefault();
}

std::vector<std::shared_ptr<Site>> SiteManager::operator*() {
  std::vector<std::shared_ptr<Site>> r;
  r.reserve(sites.size());
  for (auto it = sites.begin(); it != sites.end(); ++it)
    r.push_back(it->second);
  return r;
}

Site& SiteManager::getDefault() {
  if (defaultSite == nullptr) return *sites.begin()->second;
  return *defaultSite;
}
