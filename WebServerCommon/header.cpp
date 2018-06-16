/*
Copyright 2018 Jesse Laning
*/

#include <sstream>
#include "header.h"

using webserver::http::Header;
using webserver::utils::STLUtils;

Header::Header(STLUtils::ci_set<std::string> valid) : valid(valid) {}

const STLUtils::ci_map<std::string, std::string>& Header::operator*() const {
  return items;
}

std::string& Header::operator[](const std::string& item) {
  return items.insert(std::make_pair(item, std::string())).first->second;
}

std::string& Header::operator[](std::string&& item) {
  return items.try_emplace(std::move(item)).first->second;
}

const std::string& Header::operator[](const std::string& item) const {
  return items.at(item);
}

const std::string& Header::operator[](std::string&& item) const {
  return items.at(item);
}

void Header::clear() { items.clear(); }

void Header::parse(std::map<std::string, std::string>& parts) {
  for (auto it = parts.begin(); it != parts.end();) {
    auto p = *it;
    if (isValid(p.first)) {
      items[p.first] = p.second;
      parts.erase(it++);
    } else {
      ++it;
    }
  }
}

bool Header::has(const std::string& item) const {
  return items.find(item) != items.end();
}

bool Header::isValid(const std::string& val) const {
  return STLUtils::inContainer(val, valid);
}

std::string Header::build() const {
  std::ostringstream oss;
  for (auto& p : items)
    if (isValid(p.first)) oss << p.first << ": " << p.second << std::endl;
  return oss.str();
}
