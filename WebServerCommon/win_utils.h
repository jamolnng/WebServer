/*
Copyright 2018 Jesse Laning
*/

#pragma once
#ifdef _WIN32
#include <Windows.h>
#include <string>
namespace webserver {
namespace utils {
class WinUtils {
 public:
  static std::string GetLastErrorAsString();

 private:
  WinUtils() = delete;
};
}  // namespace utils
}  // namespace webserver
#endif
