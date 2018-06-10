/*
Copyright 2018 Jesse Laning
*/

#include "status_code.h"
#include "test_plugin.h"
#include "wsc_version.h"

using webserver::http::request::Request;
using webserver::http::request::RequestLine;
using webserver::http::response::Response;
using webserver::http::response::StatusCode;

bool TestPlugin::getErrorMessage(int code, std::string& body, Request& request,
                                 Response& response) {
  RequestLine& line = request.getRequestLine();
  response.getEntityHeader()["Content-Type"] = "text/plain";
  body = "This error was handled by a plugin.\n\n";
  body += "Error " + std::to_string(code) + ": " + StatusCode::getString(code) +
          "\n" + line["Method"] + " | " + line["Request-URI"] + " | " +
          line["HTTP-Version"] + "\nWSC/" + WSC_VER_STR;
  return true;
}