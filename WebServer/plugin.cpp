/*
Copyright 2018 Jesse Laning
*/

#include "plugin.h"

using webserver::http::request::Request;
using webserver::http::response::Response;
using webserver::plugin::Plugin;

bool Plugin::modifyRequest(Request& request) { return false; }

bool Plugin::getMessage(std::string& body, Request& request,
                        Response& response) {
  return false;
}

bool Plugin::getErrorMessage(int code, std::string& body, Request& request,
                             Response& response) {
  return false;
}

bool Plugin::getResponse(Response& response) { return false; }
