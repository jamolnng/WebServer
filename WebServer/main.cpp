/*
Copyright 2018 Jesse Laning
*/

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

#include "webserver.h"

#include "logger.h"
#include "server_config.h"

using webserver::utils::Logger;

int main(int argc, char* argv[]) {
  Logger& logger = Logger::instance();
#ifdef _DEBUG
  logger.addStream(&std::cout);
#endif

  std::filesystem::path p(argv[0]);
  p = p.parent_path() / "webserver.cfg";
  std::shared_ptr<webserver::ServerConfig> config =
      std::make_shared<webserver::ServerConfig>(p);

  try {
    webserver::WebServer server(config);
    server.start();

    std::string line;
    while (server.isRunning() && std::getline(std::cin, line)) {
      if (line == "q") break;
    }
    server.stop();
  } catch (const std::runtime_error& err) {
    logger.critical(err.what());
    return -1;
  }

  return 0;
}
