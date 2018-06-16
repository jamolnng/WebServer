/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "config_map.h"
#include "error.h"
#include "lib_utils.h"
#include "mime_types.h"
#include "plugin.h"
#include "request.h"
#include "response.h"
#include "server_config.h"
namespace webserver {
namespace site {
class LIBEXPORT Site {
 public:
  explicit Site(const std::filesystem::path& site,
                const std::shared_ptr<ServerConfig>& serverConfig);

  const std::string& getName() const;
  const int getPort() const;
  const std::filesystem::path& getRoot() const;
  const bool isDefault() const;

  const std::filesystem::path getRequestURI(
      const http::request::Request& request,
      const std::vector<std::string>& extensions = {});
  const std::string getDefaultMessage(const std::filesystem::path& uri,
                                      const http::request::Request& request,
                                      http::response::Response& response);
  const std::string getDefaultErrorMessage(
      const http::error::Error& error, const http::request::Request& request,
      http::response::Response& response) noexcept;
  const std::string getMessage(
      const http::request::Request& request, http::response::Response& response,
      const std::vector<std::shared_ptr<plugin::Plugin>>& plugins);
  const std::string getErrorMessage(
      const http::error::Error& error, const http::request::Request& request,
      http::response::Response& response,
      const std::vector<std::shared_ptr<plugin::Plugin>>& plugins);

 private:
  FileConfigMap<std::string, std::string, '='> config;
  std::string name;
  int port;
  std::filesystem::path root;
  bool defaultSite;
  std::shared_ptr<ServerConfig> serverConfig;
};
}  // namespace site
}  // namespace webserver
