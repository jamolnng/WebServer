/*
Copyright 2018 Jesse Laning
*/

#include "request.h"

#include "http_utils.h"

using webserver::http::entity::EntityHeader;
using webserver::http::message::GeneralHeader;
using webserver::http::request::Request;
using webserver::http::request::RequestHeader;
using webserver::http::request::RequestLine;
using webserver::utils::HTTPUtils;
using webserver::utils::StringUtils;

void Request::clear() {
  requestLine.clear();
  generalHeader.clear();
  requestHeader.clear();
  entityHeader.clear();
  body.clear();
  uriData.clear();
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

void Request::parseBody(const std::string& str) {
  this->body = str;
  if (entityHeader.has("Content-Type")) {
    if (entityHeader["Content-Type"] == "application/x-www-form-urlencoded") {
      uriData = HTTPUtils::parseURLEncoded(body);
    } else if (entityHeader["Content-Type"] == "multipart/form-data") {
      // formData = HTTPUtils::parseFormData(body);
    }
  }
}

const RequestLine& Request::getRequestLine() const { return requestLine; }

const GeneralHeader& Request::getGeneralHeader() const { return generalHeader; }

const RequestHeader& Request::getRequestHeader() const { return requestHeader; }

const EntityHeader& Request::getEntityHeader() const { return entityHeader; }

const std::string& Request::getBody() const { return body; }

const std::map<std::string, std::string>& Request::getURIDecodedBody() const {
  return uriData;
}