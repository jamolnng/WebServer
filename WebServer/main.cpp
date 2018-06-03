#include <Windows.h>
#include <string>
#include <iostream>
#include <algorithm>
#include "plugin_manager.h"
#include "config.h"

extern "C" __declspec(dllexport) int webserverMain(int argc, char* argv[])
{
	std::filesystem::path p(argv[0]);
	p = p.parent_path() / "webserver.cfg";
	webserver::config::Config c(p);
	webserver::plugin::PluginManager pm(c);
	if(pm.hasPlugin("PluginTest"))
		std::cout << pm.getPlugin("PluginTest")->getName() << std::endl;
	return 0;
}