/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <string>
#include <vector>
#include "config.h"
#include "plugin.h"
#include "request.h"
namespace webserver {
namespace site {
class Site {
 public:
  explicit Site(const std::filesystem::path& site);

  const std::string& getName() const;
  const int getPort() const;
  const std::filesystem::path& getRoot() const;
  const bool isDefault() const;

  const std::string getDefaultMessage(http::request::Request& request);
  const std::string getDefaultErrorMessage(
      int code, http::request::Request& request) noexcept;
  const std::string getMessage(http::request::Request& request,
                               const std::vector<plugin::Plugin*>& plugins);
  const std::string getErrorMessage(
      int code, http::request::Request& request,
      const std::vector<plugin::Plugin*>& plugins);

 private:
  Config config;
  std::string name;
  int port;
  std::filesystem::path root;
  bool defaultSite;
};
}  // namespace site
}  // namespace webserver
