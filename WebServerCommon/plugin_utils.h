/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <memory>
#include "lib_utils.h"
#include "plugin.h"
#include "server_config.h"

namespace webserver {
namespace utils {
namespace detail {
using std::make_shared;
using std::shared_ptr;
using std::static_pointer_cast;
using webserver::ServerConfig;
using webserver::plugin::Plugin;
using webserver::site::Site;
}  // namespace detail
class LIBEXPORT PluginUtils {
#define REGISTER_PLUGIN(plugin, ...)                               \
  namespace webserver {                                            \
  namespace utils {                                                \
  namespace detail {                                               \
  extern "C" __declspec(dllexport) Plugin* __stdcall CreatePlugin( \
      const shared_ptr<ServerConfig>& serverConfig) {              \
    return new plugin(serverConfig, ##__VA_ARGS__);                \
  }                                                                \
  }                                                                \
  }                                                                \
  }

 private:
  PluginUtils() = delete;
};
}  // namespace utils
}  // namespace webserver
