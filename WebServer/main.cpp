#include "webserver.h"
#include <iostream>

extern "C" __declspec(dllexport) int webserverMain(int argc, char* argv[])
{
	std::filesystem::path p(argv[0]);
	p = p.parent_path() / "webserver.cfg";
	webserver::config::Config c(p);

	webserver::WebServer server(c);
	server.start();

	std::string line;
	while (server.isRunning() && std::getline(std::cin, line))
	{
		if (line == "q")
			break;
	}
	server.stop();

	return 0;
}