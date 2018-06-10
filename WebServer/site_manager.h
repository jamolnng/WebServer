/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <map>
#include <memory>
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
  explicit SiteManager(const StrStrConfig<>& config, utils::MimeTypes* mimeTypes);

  void load(const std::filesystem::path& path);
  Site& get(const std::string& name);
  Site& operator[](const std::string& name);
  std::vector<std::shared_ptr<Site>> operator*();
  Site& getDefault();

 private:
  std::map<std::string, std::shared_ptr<Site>> sites;
  StrStrConfig<> config;
  std::shared_ptr<Site> defaultSite;
  utils::MimeTypes* mimeTypes{nullptr};
};
}  // namespace site
}  // namespace webserver
