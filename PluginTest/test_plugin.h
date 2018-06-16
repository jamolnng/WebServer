/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <iostream>
#include <string>
#include "brain_fuck.h"
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
      : Plugin(serverConfig), name(name) {
    serverConfig->getMimeTypes()["bf"] = "text/html";
  }

  bool getMessage(Site* site, std::string& body,
                  const webserver::http::request::Request& request,
                  webserver::http::response::Response& response) override;

  bool getErrorMessage(Site* site, const Error& error, std::string& body,
                       const webserver::http::request::Request& request,
                       webserver::http::response::Response& response) override;

 private:
  std::string name;
};

REGISTER_PLUGIN(TestPlugin, "Test Plugin")
