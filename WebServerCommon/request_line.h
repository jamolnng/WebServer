/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <string>
#include "lib_utils.h"
#include "line.h"
#include "string_utils.h"

namespace webserver {
namespace http {
namespace request {
class LIBEXPORT RequestLine : public Line {
 public:
  RequestLine() noexcept;
};
}  // namespace request
}  // namespace http
}  // namespace webserver
