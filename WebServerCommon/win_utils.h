/*
Copyright 2018 Jesse Laning
*/

#pragma once
#ifdef _WIN32
#include <Windows.h>
#include <string>
#include "lib_utils.h"
namespace webserver {
namespace utils {
class LIBEXPORT WinUtils {
 public:
  static std::string GetLastErrorAsString();

 private:
  WinUtils() = delete;
};
}  // namespace utils
}  // namespace webserver
#endif
