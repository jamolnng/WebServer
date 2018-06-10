/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <filesystem>
#include <fstream>
#include <map>
#include <string>
#include <type_traits>
#include <vector>
#include "stl_utils.h"
#include "string_utils.h"

namespace webserver {
template <typename _Key, typename _Val,
          typename _Less = webserver::utils::STLUtils::ci_less>
class ConfigMap {
 public:
  using key_type = _Key;
  using mapped_type = _Val;
  using less = _Less;
  using base_map = std::map<key_type, mapped_type, less>;

  explicit ConfigMap() = default;
  ConfigMap(const base_map& defaults)
      : ConfigMap<key_type, mapped_type, less>() {
    items.insert(defaults.begin(), defaults.end());
  }

  bool has(const key_type& key) const { return items.find(key) != items.end(); }
  mapped_type& operator[](const key_type& key) {
    return items.insert(std::make_pair(key, std::string())).first->second;
  }
  mapped_type& operator[](key_type&& key) {
    return items.try_emplace(std::move(key)).first->second;
  }
  const mapped_type& operator[](const key_type& key) const {
    return items.at(key);
  }
  const mapped_type& operator[](key_type&& key) const { return items.at(key); }

  template <typename T>
  T get(const key_type& item) const;

  template <>
  bool get<bool>(const key_type& item) const {
    return has(item);
  }

  template <>
  double get<double>(const key_type& item) const {
    return fromString<double>(items.at(item));
  }

  template <>
  int get<int>(const key_type& item) const {
    return fromString<int>(items.at(item));
  }

  template <>
  std::string get<std::string>(const key_type& item) const {
    return fromString<key_type>(items.at(item));
  }

 protected:
  base_map items;

  template <typename T>
  T fromString(const std::string& s) const;

  template <>
  int fromString<int>(const std::string& s) const {
    return std::stoi(s);
  }

  template <>
  double fromString<double>(const std::string& s) const {
    return std::stod(s);
  }

  template <>
  std::string fromString<std::string>(const std::string& s) const {
    return s;
  }

  template <typename T>
  std::string toString(const T& t) const {
    return std::to_string(t);
  }

  template <>
  std::string toString<std::string>(const std::string& t) const {
    return t;
  }

  key_type toKey(const std::string& k) const { return fromString<key_type>(k); }

  mapped_type toMapped(const std::string& m) const {
    return fromString<mapped_type>(m);
  }
};

template <typename _Key, typename _Val, char _Sep,
          typename _Less = webserver::utils::STLUtils::ci_less>
class FileConfigMap : public ConfigMap<_Key, _Val, _Less> {
 public:
  using _MyBase = ConfigMap<_Key, _Val, _Less>;
  using key_type = _Key;
  using mapped_type = _Val;
  using less = _Less;
  using base_map = std::map<key_type, mapped_type, less>;
  static const char seperator = _Sep;

  FileConfigMap() : _MyBase() {}

  FileConfigMap(const base_map& defaults)
      : _MyBase(defaults) {}

  void virtual load(const std::filesystem::path& file) {
    std::ifstream in(file, std::ios::binary);
    if (in) {
      std::string line;
      std::string strItem;
      std::string strVal;
      std::vector<std::string> s;
      while (getline(in, line)) {
        utils::StringUtils::trim(line);
        if (line.empty()) continue;
        if (line[0] == '#') continue;

        s = utils::StringUtils::split(line, seperator, 2);
        strItem = s[0];
        utils::StringUtils::trim(strItem);

        if (s.size() == 2)
          strVal = s[1];
        else
          strVal = "";
        utils::StringUtils::trim(strVal);

        key_type item = _MyBase::toKey(strItem);
        mapped_type val = _MyBase::toMapped(strVal);
        this->items[item] = val;
      }
      in.close();
    }
  }

 private:
};
}  // namespace webserver
