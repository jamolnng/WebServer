/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <map>
#include <set>
#include <string>
#include "lib_utils.h"
#include "stl_utils.h"
namespace webserver {
namespace http {
class LIBEXPORT Header {
 public:
  std::string& operator[](const std::string& item);
  std::string& operator[](std::string&& item);
  const std::string& operator[](const std::string& item) const;
  const std::string& operator[](std::string&& item) const;
  void clear();
  bool has(const std::string& item) const;
  const utils::STLUtils::ci_map<std::string, std::string>& operator*() const;
  virtual void parse(std::map<std::string, std::string>& parts);
  virtual std::string build() const;

 protected:
  explicit Header(utils::STLUtils::ci_set<std::string> valid);

  utils::STLUtils::ci_map<std::string, std::string> items;
  utils::STLUtils::ci_set<std::string> valid;

  bool isValid(const std::string& val) const;
};
}  // namespace http
}  // namespace webserver
