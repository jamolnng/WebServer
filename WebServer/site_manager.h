/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "site.h"
#include "server_config.h"

namespace webserver {
namespace site {
class SiteManager {
 public:
  SiteManager() = default;
  explicit SiteManager(const std::shared_ptr<ServerConfig>& serverConfig);

  void load(const std::filesystem::path& path);
  Site& get(const std::string& name);
  Site& operator[](const std::string& name);
  std::vector<std::shared_ptr<Site>> operator*();
  Site& getDefault();

 private:
  std::map<std::string, std::shared_ptr<Site>> sites;
  std::shared_ptr<ServerConfig> serverConfig;
  std::shared_ptr<Site> defaultSite;
};
}  // namespace site
}  // namespace webserver
