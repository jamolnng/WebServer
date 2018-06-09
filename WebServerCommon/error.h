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
class LIBEXPORT Error : public std::exception {
 public:
  explicit Error(int code);
  const char* what() throw();
  const int code();

 private:
  Error() = delete;
  std::string message;
  int status;
};
}  // namespace error
}  // namespace http
}  // namespace webserver
