/*
Copyright 2018 Jesse Laning
*/

#include "server_config.h"

using webserver::FileConfigMap;
using webserver::ServerConfig;
using webserver::utils::MimeTypes;

ServerConfig::ServerConfig(const std::filesystem::path& path)
    : ServerConfig(path, {{"plugins", "plugins"},
                          {"sites", "sites"},
                          {"port", "80"},
                          {"timeout", "5"},
                          {"mime", "mime.types"}}) {}

ServerConfig::ServerConfig(const std::filesystem::path& path,
                           const base_map& defaults)
    : FileConfigMap<key_type, mapped_type, seperator, less>(defaults),
      parent(path.parent_path()) {
  load(path);
  mimeTypes.load(path.parent_path() / (*this)["mime"]);
}

MimeTypes& ServerConfig::getMimeTypes() { return mimeTypes; }

const std::filesystem::path& ServerConfig::getParent() { return parent; }
