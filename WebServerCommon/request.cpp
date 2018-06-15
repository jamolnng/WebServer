/*
Copyright 2018 Jesse Laning
*/

#include "request.h"

using webserver::http::entity::EntityHeader;
using webserver::http::message::GeneralHeader;
using webserver::http::request::Request;
using webserver::http::request::RequestHeader;
using webserver::http::request::RequestLine;
using webserver::utils::StringUtils;

void Request::clear() {
  requestLine.clear();
  generalHeader.clear();
  requestHeader.clear();
  entityHeader.clear();
  body.clear();
}

void Request::parse(std::vector<std::string>& lines) {
  requestLine.parse(lines[0]);
  lines.erase(lines.begin());
  std::map<std::string, std::string> parts;
  std::vector<std::string> split;
  std::string item, val;
  for (const std::string& line : lines) {
    split = StringUtils::split(line, ':', 2);
    item = split[0];
    StringUtils::trim(item);
    if (split.size() == 2)
      val = split[1];
    else
      val = "";
    StringUtils::trim(val);
    parts[item] = val;
  }
  generalHeader.parse(parts);
  requestHeader.parse(parts);
  entityHeader.parse(parts);
}

RequestLine& Request::getRequestLine() { return requestLine; }

GeneralHeader& Request::getGeneralHeader() { return generalHeader; }

RequestHeader& Request::getRequestHeader() { return requestHeader; }

EntityHeader& Request::getEntityHeader() { return entityHeader; }

std::string& Request::getBody() { return body; }