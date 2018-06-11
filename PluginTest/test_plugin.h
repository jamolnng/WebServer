/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <string>
#include "error.h"
#include "plugin_utils.h"
#include "site.h"

using webserver::ServerConfig;
using webserver::http::error::Error;
using webserver::plugin::Plugin;
using webserver::site::Site;

class TestPlugin : public Plugin {
 public:
  TestPlugin(const std::shared_ptr<ServerConfig>& serverConfig,
             const std::string& name)
      : Plugin(serverConfig), name(name) {}

  bool getErrorMessage(const Site* site, const Error& error, std::string& body,
                       webserver::http::request::Request& request,
                       webserver::http::response::Response& response) override;

 private:
  std::string name;
};

REGISTER_PLUGIN(TestPlugin, "Test Plugin")
