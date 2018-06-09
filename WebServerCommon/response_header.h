/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include "header.h"
namespace webserver {
namespace http {
namespace response {
class ResponseHeader : public Header {
 public:
  ResponseHeader() noexcept;
};
}  // namespace response
}  // namespace http
}  // namespace webserver
