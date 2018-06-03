#pragma once
#include <string>
#include "plugin.h"
#include "config.h"
#include "lib_utils.h"

namespace webserver
{
	namespace utils
	{
		using plugin::Plugin;
		using config::Config;
		class LIBEXPORT PluginUtils
		{
#define REGISTER_PLUGIN(plugin) \
extern "C" __declspec(dllexport) Plugin* __stdcall CreatePlugin(Config* config) \
{ \
	return new plugin(config); \
}

		private:
			PluginUtils() {}
		
		};
	}
}