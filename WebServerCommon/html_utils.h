/*
Copyright 2018 Jesse Laning
*/

#pragma once

#include <string>
#include "lib_utils.h"

namespace webserver {
  namespace utils {
    class LIBEXPORT HTMLUtils {
    public:
      HTMLUtils() = delete;
      HTMLUtils(HTMLUtils const&) = delete;
      void operator=(HTMLUtils const&) = delete;

      static void xmlEscape(std::string& data);

    };
  }
}
