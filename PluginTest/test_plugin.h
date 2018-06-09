/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <string>
#include "plugin_utils.h"

using webserver::Config;
using webserver::plugin::Plugin;

class TestPlugin : public webserver::plugin::Plugin {
 public:
  TestPlugin() noexcept;
};

REGISTER_PLUGIN(TestPlugin);
