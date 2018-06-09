/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <iostream>
#include <map>
#include <string>
#include "header.h"
#include "lib_utils.h"

namespace webserver {
namespace http {
namespace message {
class LIBEXPORT GeneralHeader : public Header {
 public:
  GeneralHeader() noexcept;
};
}  // namespace message
}  // namespace http
}  // namespace webserver
