/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <filesystem>
#include "lib_utils.h"
#ifdef _MSC_VER
#if _MSVC_LANG < 201703L
namespace std {
namespace filesystem = std::experimental::filesystem;
}  // namespace std
#endif
#endif

namespace webserver {
namespace utils {
class LIBEXPORT FileUtils {
 public:
  static std::filesystem::path getParent(const std::filesystem::path& p1,
                                         const std::filesystem::path& p2);

 private:
  FileUtils() = delete;
};
}  // namespace utils
}  // namespace webserver
