/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <filesystem>
#include <map>
#include <string>
#include "config_map.h"
#include "lib_utils.h"
namespace webserver {
namespace utils {
class LIBEXPORT MimeTypes
    : public FileConfigMap<std::string, std::string, ' '> {
 public:
  MimeTypes();
  MimeTypes(const base_map& defaults);

  void load(const std::filesystem::path& path) override;
};
}  // namespace utils
}  // namespace webserver
