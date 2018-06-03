#include "plugin_manager.h"
#include "file_utils.h"
#include <iostream>

using namespace webserver::plugin;

typedef Plugin*(__stdcall *CreatePlugin)();

PluginManager::PluginManager(webserver::config::Config conf) :
	config(conf)
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
#ifdef _WIN32
	for (HINSTANCE l : libs)
		FreeLibrary(l);
#else
	for (void* l : libs)
		::dlclose(l);
#endif
}

void PluginManager::loadPlugin(std::string name)
{
	CreatePlugin create;
	std::filesystem::path p(config["plugins"]);
	p /= name;
#ifdef _WIN32
	std::string ext = ".dll";
#else
	std::string ext = ".so";
#endif
	p /= name + ext;
#ifdef _WIN32
	HINSTANCE lib = LoadLibrary(p.generic_string().c_str());
	if (!lib)
	{
		std::cout << "Failed to load library" << std::endl;
		return;
	}
	create = (CreatePlugin)GetProcAddress(lib, "CreatePlugin");
#else
	void *lib = ::dlopen(p.generic_string().c_str());
	if (!lib)
	{
		std::cout << "Failed to load library" << std::endl;
		return;
	}
	create = (CreatePlugin)::dlsym(lib, "CreatePlugin");
#endif
	if (!create)
	{
		std::cout << "Failed to find plugin hook" << std::endl;
#ifdef _WIN32
		FreeLibrary(lib);
#else
		::dlclose(lib);
#endif
	}
	plugins[name] = create();
	libs.push_back(lib);
}

bool PluginManager::hasPlugin(std::string name)
{
	return plugins.find(name) != plugins.end();
}

Plugin* PluginManager::getPlugin(std::string name)
{
	if (hasPlugin(name))
		return plugins[name];
	return nullptr;
}