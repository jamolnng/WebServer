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
using webserver::http::response::Response;
using webserver::http::response::StatusCode;
using webserver::plugin::Plugin;
using webserver::site::Site;
using webserver::utils::MimeTypes;

Site::Site(const std::filesystem::path& site, MimeTypes* mimeTypes)
    : config(site, {{"name", "localhost"},
                    {"port", "80"},
                    {"root", ""},
                    {"default", "false"}}),
      mimeTypes(mimeTypes) {
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

const std::string Site::getDefaultMessage(Request& request,
                                          Response& response) {
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
  std::string ext = path.extension().string().substr(1);
  if (mimeTypes->has(ext))
    response.getEntityHeader()["Content-Type"] = (*mimeTypes)[ext];
  else
    response.getEntityHeader()["Content-Type"] = "application/unknown";
  return str;
}

const std::string Site::getDefaultErrorMessage(int code, Request& request,
                                               Response& response) noexcept {
  http::request::RequestLine& line = request.getRequestLine();
  return "Error " + std::to_string(code) + ": " + StatusCode::getString(code) +
         "\n" + line["Method"] + " | " + name + line["Request-URI"] + " | " +
         line["HTTP-Version"] + "\n" + "WS/0.0.1 WSCommon/0.0.1";
}

const std::string Site::getMessage(Request& request, Response& response,
                                   const std::vector<Plugin*>& plugins) {
  for (plugin::Plugin* p : plugins) {
    std::string body;
    if (p->getMessage(body, request)) return body;
  }
  return getDefaultMessage(request, response);
}

const std::string Site::getErrorMessage(int code, Request& request,
                                        Response& response,
                                        const std::vector<Plugin*>& plugins) {
  for (Plugin* p : plugins) {
    std::string body;
    if (p->getErrorMessage(code, body, request)) return body;
  }
  return getDefaultErrorMessage(code, request, response);
}
