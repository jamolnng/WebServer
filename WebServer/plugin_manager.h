#pragma once
#include <string>
#include <map>
#include <memory>
#include "plugin.h"
#include "config.h"
#include "file_utils.h"
#include "lib_utils.h"

namespace webserver
{
	namespace plugin
	{
		class PluginManager
		{
		public:
			PluginManager(const webserver::config::Config& config);
			~PluginManager();

			void loadPlugin(const std::string& name);
			bool hasPlugin(const std::string& name);
			const Plugin& getPlugin(const std::string& name);

		private:
			std::map<std::string, std::pair<utils::LibUtils::LIBHANDLE, Plugin*>> plugins;
			webserver::config::Config config;
		};
	}
}