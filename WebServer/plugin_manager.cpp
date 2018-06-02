#include "plugin_manager.h"
#include <iostream>

namespace windows
{
#include <Windows.h>
}

using namespace webserver::plugin;

typedef Plugin*(__stdcall *getDLLPlugin)();

PluginManager::PluginManager(std::string path) :
	path(path)
{
}

PluginManager::~PluginManager()
{
}

void PluginManager::loadPlugin(std::string name)
{
	windows::HINSTANCE dll = windows::LoadLibrary((path + "\\" + name + ".dll").c_str());
	if (!dll)
	{
		std::cout << "Failed to load DLL" << std::endl;
		return;
	}
	getDLLPlugin gp = (getDLLPlugin)windows::GetProcAddress(dll, "getPlugin");
	if (!gp)
	{
		std::cout << "Failed to load func" << std::endl;
		windows::FreeLibrary(dll);
		return;
	}
	plugins[name] = gp();
	FreeLibrary(dll);
}

bool PluginManager::hasPlugin(std::string name)
{
	return plugins.find(name) != plugins.end();
}

Plugin* PluginManager::getPlugin(std::string name)
{
	if (plugins.find(name) != plugins.end())
		return plugins[name];
	return nullptr;
}