/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <filesystem>
#include <string>
#include "config_map.h"
#include "lib_utils.h"
#include "mime_types.h"
namespace webserver {
class LIBEXPORT ServerConfig
    : public webserver::FileConfigMap<std::string, std::string, '='> {
 public:
  explicit ServerConfig(const std::filesystem::path& path);
  ServerConfig(const std::filesystem::path& path, const base_map& defaults);

  const utils::MimeTypes& getMimeTypes() const;
  const std::filesystem::path& getParent();

 private:
  utils::MimeTypes mimeTypes;
  std::filesystem::path parent;
};
}  // namespace webserver
