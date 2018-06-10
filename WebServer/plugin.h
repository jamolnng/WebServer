/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <string>
#include "lib_utils.h"
#include "request.h"
#include "response.h"

namespace webserver {
namespace plugin {
class LIBEXPORT Plugin {
 public:
  Plugin() = default;

  virtual bool modifyRequest(http::request::Request& request);
  virtual bool getMessage(std::string& body, http::request::Request& request,
                          http::response::Response& response);
  virtual bool getErrorMessage(int code, std::string& body,
                               http::request::Request& request,
                               http::response::Response& response);
  virtual bool getResponse(http::response::Response& response);
};
}  // namespace plugin
}  // namespace webserver
