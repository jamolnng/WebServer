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
  void clear();
  const bool isDone() const;
  const Request& get() const;
  bool operator!();
  RequestParser& operator<<(const std::string& str);

 private:
  std::string buf{};
  Request request{};
  size_t offset{0};
  bool done{false};
};

}  // namespace request
}  // namespace http
}  // namespace webserver
