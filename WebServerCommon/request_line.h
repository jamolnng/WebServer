/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <map>
#include <string>
#include "lib_utils.h"
#include "line.h"
#include "string_utils.h"

namespace webserver {
namespace http {
namespace request {
class LIBEXPORT RequestLine : public Line {
 public:
  RequestLine() noexcept;

  const std::string& getURI() const;
  const std::map<std::string, std::string>& getParsedQuery() const;
  const std::string& getQuery() const;

  void clear() override;
  void parse(const std::string& line) override;

 private:
  std::string uri;
  std::map<std::string, std::string> parsedQuery;
  std::string query;
};
}  // namespace request
}  // namespace http
}  // namespace webserver
