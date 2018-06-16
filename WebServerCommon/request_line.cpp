/*
Copyright 2018 Jesse Laning
*/

#include <vector>
#include "http_utils.h"
#include "request_line.h"
#include "string_utils.h"

using webserver::http::request::RequestLine;
using webserver::utils::HTTPUtils;
using webserver::utils::StringUtils;

RequestLine::RequestLine() noexcept
    : Line({"Method", "Request-URI", "HTTP-Version"}) {}

const std::string& RequestLine::getURI() const { return uri; }

const std::map<std::string, std::string>& RequestLine::getParsedQuery() const {
  return parsedQuery;
}

const std::string& RequestLine::getQuery() const { return query; }

void RequestLine::clear() {
  Line::clear();
  uri.clear();
  query.clear();
  parsedQuery.clear();
}

void RequestLine::parse(const std::string& line) {
  Line::parse(line);
  std::vector<std::string> split =
      StringUtils::split(items["Request-URI"], '?', 2);
  uri = split[0];
  if (split.size() == 2) {
    query = split[1];
    parsedQuery = HTTPUtils::parseURLEncoded(split[1]);
  }
}
