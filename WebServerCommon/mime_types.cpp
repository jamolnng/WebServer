/*
Copyright 2018 Jesse Laning
*/

#include "mime_types.h"

#include <fstream>
#include <iostream>
#include <vector>
#include "string_utils.h"

using webserver::FileConfigMap;
using webserver::utils::MimeTypes;
using webserver::utils::StringUtils;

MimeTypes::MimeTypes() : FileConfigMap<std::string, std::string, ' '>() {}

MimeTypes::MimeTypes(const base_map& defaults)
    : FileConfigMap<std::string, std::string, ' '>(defaults) {}

void MimeTypes::load(const std::filesystem::path& path) {
  std::ifstream in(path, std::ios::binary);
  std::string line;
  while (std::getline(in, line)) {
    std::vector<std::string> splitType = StringUtils::split(line, ' ', 2);
    if (splitType.size() == 2) {
      std::string type = splitType[0];
      std::vector<std::string> splitExt = StringUtils::split(splitType[1], ' ');
      for (auto& s : splitExt) items[s] = type;
    }
  }
}
