/*
Copyright 2018 Jesse Laning
*/

#include <vector>
#include "request_parser.h"
#include "string_utils.h"

using webserver::http::request::Request;
using webserver::http::request::RequestParser;

void RequestParser::parseHeader(const std::string& str) {
  buf += str;
  size_t end;
  if (buf.size() - str.size() < 3)
    end = buf.find("\r\n\r\n");
  else
    end = buf.find("\r\n\r\n", buf.size() - str.size() - 3);
  if (end != std::string::npos) {
    std::vector<std::string> lines =
        utils::StringUtils::split(buf.substr(0, end), '\n');
    request.parse(lines);
    if (request.getEntityHeader().has("Content-Length")) {
      state = PARSE_BODY;
      buf = buf.substr(end + 4);
      contentLength = std::stoul(request.getEntityHeader()["Content-Length"]);
      // edge case where body is fully contained in recieved string
      parseBody("");
    } else {
      done = true;
      buf.clear();
    }
  }
}

void RequestParser::parseBody(const std::string& str) {
  buf += str;
  if (buf.size() >= contentLength) {
    done = true;
    state = PARSE_HEADER;
    request.getBody() = buf.substr(0, contentLength);
    buf = buf.substr(contentLength);
    // edge case where next header is fully contained in recieved string
    parseHeader("");
  }
}

void RequestParser::parse(const std::string& str) {
  switch (state) {
    case PARSE_HEADER:
      parseHeader(str);
      break;
    case PARSE_BODY:
      parseBody(str);
      break;
  }
}

void RequestParser::clear() {
  request.clear();
  done = false;
  state = PARSE_HEADER;
}

const bool RequestParser::isDone() const { return done; }

const Request& RequestParser::get() const { return request; }

bool RequestParser::operator!() { return !done; }

RequestParser& RequestParser::operator<<(const std::string& str) {
  parse(str);
  return *this;
}
