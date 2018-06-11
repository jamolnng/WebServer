/*
Copyright 2018 Jesse Laning
*/

#include "plugin.h"
#include "site.h"

using webserver::ServerConfig;
using webserver::http::error::Error;
using webserver::http::request::Request;
using webserver::http::response::Response;
using webserver::plugin::Plugin;
using webserver::site::Site;

Plugin::Plugin(const std::shared_ptr<ServerConfig>& serverConfig)
    : serverConfig(serverConfig) {}

bool Plugin::modifyRequest(Request& request) { return false; }

bool Plugin::getMessage(const Site* site, std::string& body, Request& request,
                        Response& response) {
  return false;
}

bool Plugin::getErrorMessage(const Site* site, const Error& error,
                             std::string& body, Request& request,
                             Response& response) {
  return false;
}
