/*
Copyright 2018 Jesse Laning
*/

#include <filesystem>
#include <regex>
#include <sstream>
#include "brain_fuck.h"
#include "html_utils.h"
#include "http_utils.h"
#include "logger.h"
#include "status_code.h"
#include "string_utils.h"
#include "test_plugin.h"
#include "wsc_version.h"

using webserver::http::request::Request;
using webserver::http::request::RequestLine;
using webserver::http::response::Response;
using webserver::http::response::StatusCode;
using webserver::utils::HTMLUtils;
using webserver::utils::HTTPUtils;
using webserver::utils::Logger;
using webserver::utils::StringUtils;

static const std::regex bfr("<\\s*\\?\\s*bf\\s([\\S\\s]*?)\\s*\\?\\s*>");
static BrainFuck<> bf;

Logger& logger = Logger::instance();

bool TestPlugin::getMessage(const Site* site, std::string& body,
                            const Request& request, Response& response) {
  std::filesystem::path uri = site->getRequestURI(request, {".bf"});
  if (uri.extension() != ".bf") return false;

  // test of logger singleton in plugins
  logger.info("Parsing BrainFuck request: " +
              request.getRequestLine()["Request-URI"]);

  std::string regex = site->getDefaultMessage(uri, request, response);
  std::string str = regex;
  std::sregex_iterator iter(regex.begin(), regex.end(), bfr);
  std::sregex_iterator end;
  size_t removed = 0;
  while (iter != end) {
    if (iter->size() == 2) {
      std::string rlq = request.getRequestLine().getQuery();
      std::string rb = request.getBody();
      std::string sep = (rlq.empty() || rb.empty()) ? "" : "&";
      std::istringstream in(HTTPUtils::urlDecode(rlq + sep + rb));
      std::ostringstream out;
      bf.compile((*iter)[1]);
      bf.exec(in, out);
      std::string run = out.str();
      StringUtils::trim(run);
      HTMLUtils::xmlEscape(run);
      auto len = (*iter)[0].length();
      str.replace((*iter).position(0) - removed, len, run);
      removed += len - run.size();
    }
    ++iter;
  }
  body = str;
  return true;
}

bool TestPlugin::getErrorMessage(const Site* site, const Error& error,
                                 std::string& body, const Request& request,
                                 Response& response) {
  const RequestLine& line = request.getRequestLine();
  response.getEntityHeader()["Content-Type"] = "text/plain";
  body = "This error was handled by a plugin: " + name + ".\n\n";
  body += "Error " + std::to_string(error.code()) + ": " + error.what() + "\n" +
          line["Method"] + " | " + site->getName() + line["Request-URI"] +
          " | " + line["HTTP-Version"] + "\nWScommon/" + WSC_VER_STR;
  return true;
}