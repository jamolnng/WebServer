/*
Copyright 2018 Jesse Laning
*/

#include <chrono>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <streambuf>
#include "error.h"
#include "file_utils.h"
#include "site.h"
#include "status_code.h"
#include "wsc_version.h"

using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::chrono::time_point;
using webserver::http::error::Error;
using webserver::http::request::Request;
using webserver::http::response::Response;
using webserver::http::response::StatusCode;
using webserver::plugin::Plugin;
using webserver::site::Site;
using webserver::utils::MimeTypes;
namespace fs = std::filesystem;

Site::Site(const fs::path& site, MimeTypes* mimeTypes)
    : config(site, {{"name", "localhost"},
                    {"port", "80"},
                    {"root", ""},
                    {"default", "false"}}),
      mimeTypes(mimeTypes),
      name(config["name"]),
      port(config.get<int>("port")),
      root(config["root"]),
      defaultSite(config.get<bool>("default")) {
  if (root.is_relative())
    root = std::filesystem::absolute(config.getParent() / root);
}

const std::string& Site::getName() const { return name; }

const int Site::getPort() const { return port; }

const fs::path& Site::getRoot() const { return root; }

const bool Site::isDefault() const { return defaultSite; }

const std::string Site::getDefaultMessage(Request& request,
                                          Response& response) {
  http::request::RequestLine& reqLine = request.getRequestLine();
  http::entity::EntityHeader& resEntity = response.getEntityHeader();

  fs::path uri = reqLine["Request-URI"];
  if (uri.has_root_directory()) uri = uri.relative_path();
  uri = root / uri;
  if (std::filesystem::is_directory(uri)) uri = uri / "index.html";
  if (!std::filesystem::exists(uri)) throw Error(StatusCode::NOT_FOUND);
  std::ifstream in(uri, std::ios::binary);
  if (!in) throw Error(StatusCode::INTERNAL_SERVER_ERROR);
  std::string str;
  in.seekg(0, std::ios::end);
  str.reserve(static_cast<size_t>(in.tellg()));
  in.seekg(0, std::ios::beg);
  str.assign(std::istreambuf_iterator<char>(in),
             std::istreambuf_iterator<char>());
  in.close();

  auto s = duration_cast<seconds>(
      std::filesystem::last_write_time(uri).time_since_epoch());
  auto lwt = time_point<system_clock>(s);
  auto lwt_c = system_clock::to_time_t(lwt);
  std::stringstream date;
  date << std::put_time(std::gmtime(&lwt_c), "%a, %e %b %Y %T GMT");
  resEntity["Last-Modified"] = date.str();

  std::string ext = uri.extension().string().substr(1);
  if (mimeTypes->has(ext))
    resEntity["Content-Type"] = (*mimeTypes)[ext];
  else
    resEntity["Content-Type"] = "application/unknown";
  return str;
}

const std::string Site::getDefaultErrorMessage(int code, Request& request,
                                               Response& response) noexcept {
  http::request::RequestLine& line = request.getRequestLine();
  return "Error " + std::to_string(code) + ": " + StatusCode::getString(code) +
         "\n" + line["Method"] + " | " + name + line["Request-URI"] + " | " +
         line["HTTP-Version"] + "\nWSCommon" + WSC_VER_STR;
}

const std::string Site::getMessage(
    Request& request, Response& response,
    const std::vector<std::shared_ptr<Plugin>>& plugins) {
  for (auto& p : plugins) {
    std::string body;
    if (p->getMessage(body, request, response)) return body;
  }
  return getDefaultMessage(request, response);
}

const std::string Site::getErrorMessage(
    int code, Request& request, Response& response,
    const std::vector<std::shared_ptr<Plugin>>& plugins) {
  for (auto& p : plugins) {
    std::string body;
    if (p->getErrorMessage(code, body, request, response)) return body;
  }
  return getDefaultErrorMessage(code, request, response);
}
