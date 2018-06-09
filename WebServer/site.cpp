/*
Copyright 2018 Jesse Laning
*/

#include <fstream>
#include <streambuf>
#include "error.h"
#include "file_utils.h"
#include "site.h"
#include "status_code.h"

using webserver::http::error::Error;
using webserver::http::request::Request;
using webserver::http::response::StatusCode;
using webserver::plugin::Plugin;
using webserver::site::Site;

Site::Site(const std::filesystem::path& site)
    : config(site, {{"name", "localhost"},
                    {"port", "80"},
                    {"root", ""},
                    {"default", "false"}}) {
  name = config["name"];
  port = config.get<int>("port");
  root = config["root"];
  defaultSite = config.get<bool>("default");
  if (root.is_relative())
    root = std::filesystem::absolute(config.getParent() / root);
}

const std::string& Site::getName() const { return name; }

const int Site::getPort() const { return port; }

const std::filesystem::path& Site::getRoot() const { return root; }

const bool Site::isDefault() const { return defaultSite; }

const std::string Site::getDefaultMessage(Request& request) {
  std::filesystem::path path = request.getRequestLine()["Request-URI"];
  if (path.has_root_directory()) path = path.relative_path();
  path = root / path;
  if (std::filesystem::is_directory(path)) path = path / "index.html";
  if (!std::filesystem::exists(path)) throw Error(StatusCode::NOT_FOUND);
  std::ifstream in(path, std::ios::binary);
  if (!in) throw Error(StatusCode::INTERNAL_SERVER_ERROR);
  std::string str;
  in.seekg(0, std::ios::end);
  str.reserve(in.tellg());
  in.seekg(0, std::ios::beg);
  str.assign((std::istreambuf_iterator<char>(in)),
             std::istreambuf_iterator<char>());
  in.close();
  return str;
}

const std::string Site::getDefaultErrorMessage(int code,
                                               Request& request) noexcept {
  http::request::RequestLine& line = request.getRequestLine();
  return "Error " + std::to_string(code) + ": " + StatusCode::getString(code) +
         "\n" + line["Method"] + " \| " + name + line["Request-URI"] + " \| " +
         line["HTTP-Version"] + "\n" + "WS/0.0.1 WSCommon/0.0.1";
}

const std::string Site::getMessage(Request& request,
                                   const std::vector<Plugin*>& plugins) {
  for (plugin::Plugin* p : plugins) {
    std::string body;
    if (p->getMessage(body, request)) return body;
  }
  return getDefaultMessage(request);
}

const std::string Site::getErrorMessage(int code, Request& request,
                                        const std::vector<Plugin*>& plugins) {
  for (Plugin* p : plugins) {
    std::string body;
    if (p->getErrorMessage(code, body, request)) return body;
  }
  return getDefaultErrorMessage(code, request);
}
