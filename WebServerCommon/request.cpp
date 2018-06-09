/*
Copyright 2018 Jesse Laning
*/

#include "request.h"

using webserver::http::request::Request;
using webserver::http::request::RequestHeader;
using webserver::http::request::RequestLine;

void Request::clear() {
  requestLine.clear();
  generalHeader.clear();
  requestHeader.clear();
  entityHeader.clear();
}

void Request::parse(std::vector<std::string>& lines) {
  requestLine.parse(lines[0]);
  lines.erase(lines.begin());
  std::map<std::string, std::string> parts;
  std::vector<std::string> split;
  std::string item, val;
  for (const std::string& line : lines) {
    split = utils::StringUtils::split(line, ':', 2);
    item = split[0];
    utils::StringUtils::trim(item);
    if (split.size() == 2)
      val = split[1];
    else
      val = "";
    utils::StringUtils::trim(val);
    parts[item] = val;
  }
  generalHeader.parse(parts);
  requestHeader.parse(parts);
  entityHeader.parse(parts);
}

RequestLine& webserver::http::request::Request::getRequestLine() {
  return requestLine;
}

webserver::http::message::GeneralHeader&
webserver::http::request::Request::getGeneralHeader() {
  return generalHeader;
}

RequestHeader& webserver::http::request::Request::getRequestHeader() {
  return requestHeader;
}

webserver::http::entity::EntityHeader&
webserver::http::request::Request::getEntityHeader() {
  return entityHeader;
}
