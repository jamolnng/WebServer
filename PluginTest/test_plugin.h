#pragma once
#include <string>
#include "plugin_utils.h"

using webserver::plugin::Plugin;
using webserver::config::Config;

class TestPlugin :
	public webserver::plugin::Plugin
{
public:
	TestPlugin(const webserver::config::Config* config);
};

REGISTER_PLUGIN(TestPlugin);