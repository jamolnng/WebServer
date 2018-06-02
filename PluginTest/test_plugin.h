#pragma once
#include <string>
#include "plugin.h"

class TestPlugin :
	public webserver::plugin::Plugin
{
public:
	TestPlugin();
};

extern "C" __declspec(dllexport) webserver::plugin::Plugin* __stdcall getPlugin()
{
	return new TestPlugin();
}