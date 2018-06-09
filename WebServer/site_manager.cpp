/*
Copyright 2018 Jesse Laning
*/

#include "site_manager.h"

using webserver::site::Site;
using webserver::site::SiteManager;

SiteManager::SiteManager(const webserver::Config& conf) : config(conf) {
  std::filesystem::path sites(config["sites"]);
  if (sites.is_relative()) sites = config.getParent() / sites;
  if (std::filesystem::exists(sites))
    for (auto& di : std::filesystem::directory_iterator(sites))
      if (!std::filesystem::is_directory(di.path()))
        load(di.path().generic_string());
}

SiteManager::~SiteManager() {}

void SiteManager::load(const std::filesystem::path& path) {
  Site s(path);
  sites.insert({s.getName(), s});
  if (s.isDefault()) defaultSite = &sites.find(s.getName())->second;
}

Site& SiteManager::get(const std::string& name) {
  if (sites.find(name) != sites.end()) return sites.find(name)->second;
  return getDefault();
}

Site& SiteManager::operator[](const std::string& name) {
  if (sites.find(name) != sites.end()) return sites.find(name)->second;
  return getDefault();
}

std::vector<Site*> SiteManager::operator*() {
  std::vector<Site*> r;
  r.reserve(sites.size());
  for (auto it = sites.begin(); it != sites.end(); ++it)
    r.push_back(&(it->second));
  return r;
}

Site& SiteManager::getDefault() {
  if (defaultSite == nullptr) return sites.begin()->second;
  return *defaultSite;
}
