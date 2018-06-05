#include "plugin_manager.h"
#include "file_utils.h"
#include <iostream>

using namespace webserver::plugin;

typedef Plugin*(__stdcall *CreatePlugin)();

PluginManager::PluginManager(const webserver::config::Config& conf) :
	config(conf)
{
	std::filesystem::path plugins(config["plugins"]);
	if (std::filesystem::exists(plugins))
		for (auto& di : std::filesystem::directory_iterator(plugins))
			if (std::filesystem::is_directory(di.path()))
				if (std::filesystem::exists(di.path() / "plugin.cfg"))
					loadPlugin(di.path().filename().generic_string());
}

PluginManager::~PluginManager()
{
	for (auto& plugin : plugins)
		utils::LibUtils::dlclose(plugin.second.first);
}

void PluginManager::loadPlugin(const std::string& name)
{
	std::filesystem::path p(config["plugins"]);
	p /= name;
	p /= name + utils::LibUtils::libExt;
	std::string libPath = p.generic_string();
	auto lib = utils::LibUtils::dlopen(libPath, RTLD_LAZY);
	if (!lib)
	{
		std::cout << utils::LibUtils::dlerror() << std::endl;
		return;
	}
	CreatePlugin create = (CreatePlugin)utils::LibUtils::dlsym(lib, "CreatePlugin");
	if (!create)
	{
		std::cout << utils::LibUtils::dlerror() << std::endl;
		utils::LibUtils::dlclose(lib);
		return;
	}
	plugins[name] = { lib, create() };
}

bool PluginManager::hasPlugin(const std::string& name)
{
	return plugins.find(name) != plugins.end();
}

const Plugin& PluginManager::getPlugin(const std::string& name)
{
	return *(plugins[name].second);
}