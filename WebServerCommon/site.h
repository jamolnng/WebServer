/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <memory>
#include <string>
#include <vector>
#include "config.h"
#include "lib_utils.h"
#include "mime_types.h"
#include "plugin.h"
#include "request.h"
#include "response.h"
namespace webserver {
namespace site {
class LIBEXPORT Site {
 public:
  explicit Site(const std::filesystem::path& site, utils::MimeTypes* mimeTypes);

  const std::string& getName() const;
  const int getPort() const;
  const std::filesystem::path& getRoot() const;
  const bool isDefault() const;

  const std::string getDefaultMessage(http::request::Request& request,
                                      http::response::Response& response);
  const std::string getDefaultErrorMessage(
      int code, http::request::Request& request,
      http::response::Response& response) noexcept;
  const std::string getMessage(
      http::request::Request& request, http::response::Response& response,
      const std::vector<std::shared_ptr<plugin::Plugin>>& plugins);
  const std::string getErrorMessage(
      int code, http::request::Request& request,
      http::response::Response& response,
      const std::vector<std::shared_ptr<plugin::Plugin>>& plugins);

 private:
  StrStrConfig<> config;
  std::string name;
  int port;
  std::filesystem::path root;
  bool defaultSite;
  utils::MimeTypes* mimeTypes{nullptr};
};
}  // namespace site
}  // namespace webserver