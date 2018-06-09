/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <map>
#include <set>
#include <string>
#include "lib_utils.h"
namespace webserver {
namespace http {
class LIBEXPORT Header {
 public:
  std::string& operator[](const std::string& item);
  std::string& operator[](std::string&& item);
  void clear();
  bool has(const std::string& item);
  const std::map<std::string, std::string>& operator*() const;
  virtual void parse(std::map<std::string, std::string>& parts);
  virtual std::string build();

 protected:
  explicit Header(std::set<std::string> valid);

  std::map<std::string, std::string> items;
  std::set<std::string> valid;

  bool isValid(const std::string& val);

  template <typename Container>
  static bool inContainer(const std::string val, const Container& cont) {
    return std::find(cont.begin(), cont.end(), val) != cont.end();
  }
};
}  // namespace http
}  // namespace webserver
