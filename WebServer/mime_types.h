#pragma once
#include <map>
#include <string>
#include "file_utils.h"
#include "stl_utils.h"
namespace webserver {
namespace utils {
class MimeTypes {
 public:
  MimeTypes() = default;
  MimeTypes(const std::filesystem::path& path);

  std::string& operator[](const std::string& item);
  std::string& operator[](std::string&& item);
  void load(const std::filesystem::path& path);
  void clear();
  bool has(const std::string& item);
  const utils::STLUtils::ci_map<std::string, std::string>& operator*() const;

 private:
  STLUtils::ci_map<std::string, std::string> items;
};
}  // namespace utils
}  // namespace webserver
