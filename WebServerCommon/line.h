/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>
#include "lib_utils.h"
#include "stl_utils.h"
namespace webserver {
namespace http {
class LIBEXPORT Line {
 public:
  std::string& operator[](const std::string& item);
  std::string& operator[](std::string&& item);
  const std::string& operator[](const std::string& item) const;
  const std::string& operator[](std::string&& item) const;
  const utils::STLUtils::ci_map<std::string, std::string>& operator*() const;
  virtual void clear();
  virtual void parse(const std::string& line);
  virtual std::string build();

 protected:
  explicit Line(std::vector<std::string> names);

  utils::STLUtils::ci_set<std::string> name_set;
  std::vector<std::string> name_vec;
  utils::STLUtils::ci_map<std::string, std::string> items;

  bool isValid(const std::string& val);
};
}  // namespace http
}  // namespace webserver
