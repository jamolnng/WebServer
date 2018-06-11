/*
Copyright 2018 Jesse Laning
*/

#include <iostream>

#include <cassert>
#include <chrono>
#include <fstream>
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
using webserver::ServerConfig;
using webserver::http::entity::EntityHeader;
using webserver::http::error::Error;
using webserver::http::request::Request;
using webserver::http::request::RequestLine;
using webserver::http::response::Response;
using webserver::http::response::StatusCode;
using webserver::plugin::Plugin;
using webserver::site::Site;
namespace fs = std::filesystem;

template <typename DstTimePointT, typename SrcTimePointT,
          typename DstClockT = typename DstTimePointT::clock,
          typename SrcClockT = typename SrcTimePointT::clock>
DstTimePointT clock_cast(const SrcTimePointT tp) {
  const auto src_now = SrcClockT::now();
  const auto dst_now = DstClockT::now();
  return dst_now + (tp - src_now);
}

Site::Site(const fs::path& site,
           const std::shared_ptr<ServerConfig>& serverConfig)
    : serverConfig(serverConfig),
      config({{"name", "localhost"},
              {"port", "80"},
              {"root", ""},
              {"default", "false"}}) {
  config.load(site);
  name = config["name"];
  port = config.get<int>("port");
  root = config["root"];
  defaultSite = config["default"] == "true";
  if (root.is_relative())
    root = std::filesystem::absolute(site.parent_path() / root);
}

const std::string& Site::getName() const { return name; }

const int Site::getPort() const { return port; }

const fs::path& Site::getRoot() const { return root; }

const bool Site::isDefault() const { return defaultSite; }

const std::string Site::getDefaultMessage(Request& request,
                                          Response& response) {
  RequestLine& reqLine = request.getRequestLine();
  EntityHeader& resEntity = response.getEntityHeader();

  fs::path uri = reqLine["Request-URI"];
  if (uri.has_root_directory()) uri = uri.relative_path();
  uri = root / uri;
  if (std::filesystem::is_directory(uri)) uri = uri / "index.html";
  if (!std::filesystem::exists(uri)) throw Error(StatusCode::NOT_FOUND);
  std::string str;

  std::ifstream in;
  try {
    in.open(uri, std::ios::binary);
    in.exceptions(std::ios::badbit | std::ios::failbit);
    in.seekg(0, std::ios::end);
    str.reserve(static_cast<size_t>(in.tellg()));
    in.seekg(0, std::ios::beg);
    str.assign(std::istreambuf_iterator<char>(in),
               std::istreambuf_iterator<char>());
  } catch (const std::ios::failure& e) {
    throw Error(StatusCode::INTERNAL_SERVER_ERROR, e.what());
  }
  if (in.is_open()) in.close();

  std::stringstream date;
  auto lwt = clock_cast<system_clock::time_point>(fs::last_write_time(uri));
  auto lwt_c = system_clock::to_time_t(lwt);
  date << std::put_time(std::gmtime(&lwt_c), "%a, %e %b %Y %T GMT");
  resEntity["Last-Modified"] = date.str();

  std::string ext = uri.extension().string().substr(1);
  if (serverConfig->getMimeTypes().has(ext))
    resEntity["Content-Type"] = serverConfig->getMimeTypes()[ext];
  else
    resEntity["Content-Type"] = "application/unknown";
  return str;
}

const std::string Site::getDefaultErrorMessage(const Error& error,
                                               Request& request,
                                               Response& response) noexcept {
  RequestLine& line = request.getRequestLine();
  response.getEntityHeader()["Content-Type"] = "text/plain";
  return "Error " + std::to_string(error.code()) + ": " + error.what() + "\n" +
         line["Method"] + " | " + name + line["Request-URI"] + " | " +
         line["HTTP-Version"] + "\nWSCommon" + WSC_VER_STR;
}

const std::string Site::getMessage(
    Request& request, Response& response,
    const std::vector<std::shared_ptr<Plugin>>& plugins) {
  for (auto& p : plugins) {
    std::string body;
    if (p->getMessage(this, body, request, response)) return body;
  }
  return getDefaultMessage(request, response);
}

const std::string Site::getErrorMessage(
    const Error& error, Request& request, Response& response,
    const std::vector<std::shared_ptr<Plugin>>& plugins) {
  for (auto& p : plugins) {
    std::string body;
    if (p->getErrorMessage(this, error, body, request, response)) return body;
  }
  return getDefaultErrorMessage(error, request, response);
}
