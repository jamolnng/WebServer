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

  bool modifyRequest(http::request::Request& request);
  bool getMessage(std::string& body, const http::request::Request& request);
  bool getErrorMessage(int code, std::string& body,
                       const http::request::Request& request);
  bool getResponse(http::response::Response& response);
};
}  // namespace plugin
}  // namespace webserver
