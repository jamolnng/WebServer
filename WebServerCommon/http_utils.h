/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <map>
#include <string>
#include "lib_utils.h"
namespace webserver {
namespace utils {
class LIBEXPORT HTTPUtils {
 public:
  static std::map<std::string, std::string> parseURLEncoded(
      const std::string& encoded);

  static std::string urlDecode(const std::string& url);

 private:
  HTTPUtils() = delete;
};
}  // namespace utils
}  // namespace webserver
