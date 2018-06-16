/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <map>
#include <string>
#include <vector>
#include "entity_header.h"
#include "general_header.h"
#include "lib_utils.h"
#include "request_header.h"
#include "request_line.h"

namespace webserver {
namespace http {
namespace request {
class LIBEXPORT Request {
 public:
  Request() noexcept {};

  void clear();
  void parse(std::vector<std::string>& lines);
  void parseBody(const std::string& body);

  const RequestLine& getRequestLine() const;
  const message::GeneralHeader& getGeneralHeader() const;
  const RequestHeader& getRequestHeader() const;
  const entity::EntityHeader& getEntityHeader() const;
  const std::string& getBody() const;
  const std::map<std::string, std::string>& getURIDecodedBody() const;

 private:
  RequestLine requestLine{};
  message::GeneralHeader generalHeader{};
  RequestHeader requestHeader{};
  entity::EntityHeader entityHeader{};
  std::string body{};
  std::map<std::string, std::string> uriData;
};
}  // namespace request
}  // namespace http
}  // namespace webserver
