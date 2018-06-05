#include "webserver.h"
#include <iostream>

int main(int argc, char* argv[])
{
	std::filesystem::path p(argv[0]);
	p = p.parent_path() / "webserver.cfg";
	webserver::config::Config c(p, { { "plugins", "plugins" }, { "sites", "sites" }, { "port", "80" }, { "timeout", "5" } });

	webserver::WebServer server(c);
	try
	{
		server.start();
	}
	catch (std::runtime_error& err)
	{
		std::cout << "Failed to start server: " << err.what() << std::endl;
		return -1;
	}

	std::string line;
	while (server.isRunning() && std::getline(std::cin, line))
	{
		if (line == "q")
			break;
	}
	server.stop();

	return 0;
}