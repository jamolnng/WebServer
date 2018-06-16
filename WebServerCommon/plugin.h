/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <filesystem>
#include <memory>
#include <string>
#include "error.h"
#include "lib_utils.h"
#include "request.h"
#include "response.h"
#include "server_config.h"

namespace webserver {
namespace site {
class Site;
}
namespace plugin {
class LIBEXPORT Plugin {
 public:
  Plugin(const std::shared_ptr<webserver::ServerConfig>& serverConfig);

  virtual bool modifyRequest(http::request::Request& request);
  virtual bool getMessage(site::Site* site, std::string& body,
                          const http::request::Request& request,
                          http::response::Response& response);
  virtual bool getErrorMessage(site::Site* site,
                               const http::error::Error& error,
                               std::string& body,
                               const http::request::Request& request,
                               http::response::Response& response);

 protected:
  std::shared_ptr<webserver::ServerConfig> serverConfig;
};
}  // namespace plugin
}  // namespace webserver
