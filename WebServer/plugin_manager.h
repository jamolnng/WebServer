#pragma once
#include <string>
#include <map>
#include <memory>
#include "plugin.h"

namespace webserver
{
	namespace plugin
	{
		class PluginManager
		{
		public:
			PluginManager(std::string path);
			~PluginManager();

			void loadPlugin(std::string name);
			bool hasPlugin(std::string name);
			Plugin* getPlugin(std::string name);

		private:
			std::map<std::string, Plugin*> plugins;
			std::string path;
		};
	}
}