/*
Copyright 2018 Jesse Laning
*/

#include <sstream>
#include "response.h"

using webserver::http::entity::EntityHeader;
using webserver::http::message::GeneralHeader;
using webserver::http::response::Response;
using webserver::http::response::ResponseHeader;
using webserver::http::response::StatusLine;

void Response::clear() {
  statusLine.clear();
  generalHeader.clear();
  responseHeader.clear();
  entityHeader.clear();
}

std::string Response::build() {
  std::ostringstream oss;
  oss << statusLine.build() << std::endl;
  oss << generalHeader.build();
  oss << responseHeader.build();
  oss << entityHeader.build();
  oss << std::endl;
  return oss.str();
}

StatusLine& Response::getStatusLine() { return statusLine; }

GeneralHeader& Response::getGeneralHeader() { return generalHeader; }

ResponseHeader& Response::getResponseHeader() { return responseHeader; }

EntityHeader& Response::getEntityHeader() { return entityHeader; }
