/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <map>
#include <string>
#include <vector>
#include "config.h"
#include "mime_types.h"
#include "site.h"

namespace webserver {
namespace site {
class SiteManager {
 public:
  SiteManager() = default;
  explicit SiteManager(const webserver::Config& config,
                       utils::MimeTypes* mimeTypes);
  ~SiteManager();

  void load(const std::filesystem::path& path);
  Site& get(const std::string& name);
  Site& operator[](const std::string& name);
  std::vector<Site*> operator*();
  Site& getDefault();

 private:
  std::map<std::string, Site> sites;
  webserver::Config config;
  Site* defaultSite{nullptr};
  utils::MimeTypes* mimeTypes{nullptr};
};
}  // namespace site
}  // namespace webserver
