/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include "config_map.h"
#include "lib_utils.h"
#include "plugin.h"

namespace webserver {
namespace utils {
using webserver::plugin::Plugin;
class LIBEXPORT PluginUtils {
#define REGISTER_PLUGIN(plugin)                                       \
  extern "C" __declspec(dllexport) Plugin* __stdcall CreatePlugin() { \
    return new plugin();                                              \
  }

 private:
  PluginUtils() = delete;
};
}  // namespace utils
}  // namespace webserver
