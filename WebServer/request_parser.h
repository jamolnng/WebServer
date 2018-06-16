/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <sstream>
#include <string>
#include "lib_utils.h"
#include "request.h"

namespace webserver {
namespace http {
namespace request {
class RequestParser {
 public:
  RequestParser() noexcept = default;

  void parse(const std::string& str);
  const bool available() const;
  const Request get();
  bool operator!() const;
  RequestParser& operator<<(const std::string& str);

 private:
  std::string buf{};
  std::vector<Request> requests{};
  Request request{};
  size_t offset{0};

  void finish();
  void parseHeader(size_t strlen);
  void parseBody();

  enum { PARSE_HEADER, PARSE_BODY } state{ PARSE_HEADER };
  size_t contentLength{0};
};

}  // namespace request
}  // namespace http
}  // namespace webserver
