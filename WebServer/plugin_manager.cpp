#include "plugin_manager.h"
#include "file_utils.h"
#include <iostream>

namespace windows
{
#include <Windows.h>
}

using namespace webserver::plugin;

typedef Plugin*(__stdcall *getDLLPlugin)();

PluginManager::PluginManager(webserver::config::Config conf) :
	conf(conf)
{
	std::filesystem::path plugins(conf["plugins"]);
	if (std::filesystem::exists(plugins))
	{
		std::filesystem::directory_iterator it(plugins);
		for (const std::filesystem::directory_entry& de : it)
		{
			const std::filesystem::path& p = de.path();
			if (std::filesystem::is_directory(p))
			{
				std::filesystem::directory_iterator pit(p);
				for (const std::filesystem::directory_entry& pde : pit)
				{
					const std::filesystem::path& pp = pde.path();
					if (!std::filesystem::is_directory(pp) && pp.has_extension())
					{
						const std::filesystem::path& filename = pp.filename();
						std::string ext = filename.extension().generic_string();
						std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
#ifdef _WIN32
						std::string lib_ext = ".dll";
#else
						std::string lib_ext = ".so";
#endif
						if (ext == lib_ext)
						{
							if (p.filename().generic_string() == filename.stem().generic_string())
							{
								loadPlugin(p.filename().generic_string());
							}
						}
					}
				}
			}
		}
	}
}

PluginManager::~PluginManager()
{
}

void PluginManager::loadPlugin(std::string name)
{
	std::filesystem::path p(conf["plugins"]);
	p /= name;
	p /= name +".dll";
	windows::HINSTANCE dll = windows::LoadLibraryW(p.c_str());
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
	windows::FreeLibrary(dll);
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