/*
Copyright 2018 Jesse Laning
*/

#include <vector>
#include "request_parser.h"
#include "string_utils.h"

using webserver::http::request::Request;
using webserver::http::request::RequestParser;

void RequestParser::parseHeader(size_t strlen) {
  size_t end;
  if (buf.size() - strlen < 3)
    end = buf.find("\r\n\r\n");
  else
    end = buf.find("\r\n\r\n", buf.size() - strlen - 3);
  if (end != std::string::npos) {
    std::vector<std::string> lines =
        utils::StringUtils::split(buf.substr(0, end), '\n');
    request.parse(lines);
    buf = buf.substr(end + 4);
    if (request.getEntityHeader().has("Content-Length")) {
      state = PARSE_BODY;
      contentLength = std::stoull(request.getEntityHeader()["Content-Length"]);
      parseBody();
    } else {
      finish();
    }
  }
}

void RequestParser::parseBody() {
  if (buf.size() >= contentLength) {
    request.getBody() = buf.substr(0, contentLength);
    finish();
    buf = buf.substr(contentLength);
    parseHeader(buf.size());
  }
}

void RequestParser::finish() {
  requests.push_back(request);
  request.clear();
  state = PARSE_HEADER;
}

void RequestParser::parse(const std::string& str) {
  buf += str;
  switch (state) {
    case PARSE_HEADER:
      parseHeader(str.size());
      break;
    case PARSE_BODY:
      parseBody();
      break;
  }
}

const bool RequestParser::available() const { return requests.size() > 0; }

const Request RequestParser::get() {
  Request r = requests.back();
  requests.pop_back();
  return r;
}

bool RequestParser::operator!() { return !available(); }

RequestParser& RequestParser::operator<<(const std::string& str) {
  parse(str);
  return *this;
}
