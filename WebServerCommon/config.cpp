/*
Copyright 2018 Jesse Laning
*/

#include <fstream>
#include "config.h"
#include "string_utils.h"

using webserver::Config;
using webserver::utils::STLUtils;

Config::Config(std::filesystem::path file) { load(file); }

Config::Config(
    std::filesystem::path file,
    std::map<std::string, std::string, STLUtils::ci_less> defaults) {
  config.insert(defaults.begin(), defaults.end());
  load(file);
}

void Config::load(const std::filesystem::path& file) {
  parent = file.parent_path();
  std::ifstream in(file, std::ios::binary);
  if (in) {
    std::string line;
    std::string item;
    std::string val;
    std::vector<std::string> s;
    while (getline(in, line)) {
      utils::StringUtils::trim(line);
      if (line.empty()) continue;
      if (line[0] == '#') continue;
      s = utils::StringUtils::split(line, '=', 2);
      item = s[0];
      utils::StringUtils::trim(item);
      if (s.size() == 2)
        val = s[1];
      else
        val = "true";
      utils::StringUtils::trim(val);
      config[item] = val;
    }
    in.close();
  }
}

bool Config::has(const std::string& item) {
  return config.find(item) != config.end();
}

std::string& Config::operator[](const std::string& item) {
  return config.insert(std::make_pair(item, std::string())).first->second;
}

std::string& Config::operator[](std::string&& item) {
  return config.try_emplace(std::move(item)).first->second;
}
