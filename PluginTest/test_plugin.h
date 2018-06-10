/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <string>
#include "plugin_utils.h"

using webserver::plugin::Plugin;

class TestPlugin : public Plugin {
 public:
  TestPlugin() = default;

  bool getErrorMessage(int code, std::string& body,
                       webserver::http::request::Request& request,
                       webserver::http::response::Response& response) override;
};

REGISTER_PLUGIN(TestPlugin);
