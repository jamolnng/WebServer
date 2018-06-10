/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <filesystem>
#include <map>
#include <string>
#include <vector>
#include "lib_utils.h"
#include "stl_utils.h"

namespace webserver {
class LIBEXPORT Config {
 public:
  explicit Config(std::filesystem::path file);
  Config(std::filesystem::path file,
         std::map<std::string, std::string, utils::STLUtils::ci_less> defaults);

  void load(const std::filesystem::path& file);
  bool has(const std::string& item);
  std::string& operator[](const std::string& item);
  std::string& operator[](std::string&& item);

  const std::filesystem::path& getParent() const { return parent; }

  template <typename T>
  T get(const std::string& item);

  template <>
  bool get<bool>(const std::string& item) {
    return config[item] == "true";
  }

  template <>
  double get<double>(const std::string& item) {
    return std::stod(config[item]);
  }

  template <>
  int get<int>(const std::string& item) {
    return std::stoi(config[item]);
  }

  template <>
  std::string get<std::string>(const std::string& item) {
    return config[item];
  }

 private:
  std::map<std::string, std::string, utils::STLUtils::ci_less> config;
  std::filesystem::path parent;
};
}  // namespace webserver
