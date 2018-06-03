#pragma once
#include <string>
#include <map>
#include <memory>
#include "plugin.h"
#include "config.h"
#include "file_utils.h"
#include <Windows.h>

namespace webserver
{
	namespace plugin
	{
		class PluginManager
		{
		public:
			PluginManager(webserver::config::Config config);
			~PluginManager();

			void loadPlugin(std::string name);
			bool hasPlugin(std::string name);
			Plugin* getPlugin(std::string name);

		private:
			std::map<std::string, Plugin*> plugins;
#ifdef _WIN32
			std::vector<HINSTANCE> libs;
#else
			std::vector<void*> libs;
#endif
			webserver::config::Config config;
		};
	}
}