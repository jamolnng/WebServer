/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <stdexcept>
#include <string>
#include "lib_utils.h"

namespace webserver {
namespace http {
namespace error {
#pragma warning(disable : 4275)
class LIBEXPORT Error : public std::exception {
 public:
  explicit Error(int code, std::string additional = std::string());
  const char* what() const throw() override;
  const char* more() const;
  const int code() const;

 private:
  Error() = delete;
  std::string message;
  std::string additional;
  int status;
};
}  // namespace error
}  // namespace http
}  // namespace webserver
