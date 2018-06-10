/*
Copyright 2018 Jesse Laning
*/

#include <sstream>
#include "line.h"
#include "string_utils.h"

using webserver::http::Line;
using webserver::utils::STLUtils;

Line::Line(std::vector<std::string> names)
    : name_vec(names), name_set(names.begin(), names.end()) {}

const STLUtils::ci_map<std::string, std::string>& Line::operator*() const {
  return items;
}

std::string& Line::operator[](const std::string& item) {
  return items.insert(std::make_pair(item, std::string())).first->second;
}

std::string& Line::operator[](std::string&& item) {
  return items.try_emplace(std::move(item)).first->second;
}

void Line::clear() { items.clear(); }

void Line::parse(const std::string& line) {
  std::vector<std::string> parts =
      utils::StringUtils::split(line, ' ', name_vec.size());
  for (size_t i = 0; i < name_vec.size(); i++) {
    items[name_vec[i]] = parts[i];
  }
}

std::string Line::build() {
  std::stringstream oss;
  for (auto& n : name_vec)
    if (isValid(n)) oss << items[n] << " ";
  return oss.str().substr(0, oss.str().size() - 1);
}

bool Line::isValid(const std::string& val) {
  return STLUtils::inContainer(val, name_set);
}
