/*
Copyright 2018 Jesse Laning
*/

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

#include "webserver.h"

#include "server_config.h"

int main(int argc, char* argv[]) {
  std::filesystem::path p(argv[0]);
  p = p.parent_path() / "webserver.cfg";
  std::shared_ptr<webserver::ServerConfig> config =
      std::make_shared<webserver::ServerConfig>(p);

  webserver::WebServer server(config);
  try {
    server.start();
  } catch (const std::runtime_error& err) {
    std::cout << "Failed to start server: " << err.what() << std::endl;
    return -1;
  }

  std::string line;
  while (server.isRunning() && std::getline(std::cin, line)) {
    if (line == "q") break;
  }
  server.stop();

  return 0;
}
