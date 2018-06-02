#include <Windows.h>
#include <string>
#include <iostream>
#include <algorithm>
#include "plugin_manager.h"
#include "config.h"

std::string stem(char* file)
{
	std::string f(file);
	std::replace(f.begin(), f.end(), '\\', '/');
	if(f.find('/'))
		f.erase(f.find_last_of('/'));
	return f;
}

int main(int argc, char* argv[])
{
	std::string s = stem(argv[0]);
	webserver::config::Config c(s + "/webserver.cfg");
	//double d = c.getDouble("asdf");
	//std::cout << d << std::endl;
	std::cout << c["plugin_dir"] << std::endl;
	std::cout << c["asdf"] << std::endl;
	webserver::plugin::PluginManager pm(s);
	pm.loadPlugin("PluginTest");
	if(pm.hasPlugin("PluginTest"))
		std::cout << pm.getPlugin("PluginTest")->getName() << std::endl;
	system("pause");
	return 0;
}