#include "site.h"
#include "error.h"
#include "status_code.h"
#include <fstream>
#include <streambuf>

using namespace webserver::site;
using namespace webserver;

Site::Site(const std::filesystem::path& site) :
	config(site, { {"name", "localhost" }, { "port", "80" }, { "root", "" }, { "default", "false" } })
{
	name = config["name"];
	port = config.get<int>("port");
	root = config["root"];
	defaultSite = config.get<bool>("default");
}

const std::string& Site::getName() const
{
	return name;
}

const int Site::getPort() const
{
	return port;
}

const std::filesystem::path& Site::getRoot() const
{
	return root;
}

const bool Site::isDefault() const
{
	return defaultSite;
}

const std::string Site::getDefaultResponseMessage(http::request::Request & request)
{
	std::filesystem::path path = root;
	if (path.is_relative())
		path = config.getParent() / path;
	path = path / request.getRequestLine()["Request-URI"];
	path = std::filesystem::canonical(path, root);
	if (path.compare(root) < 0)
		path = root;
	if (std::filesystem::is_directory(path) || !path.has_filename())
		path = path / "index.html";
	if (!std::filesystem::exists(path))
		throw error::Error(http::response::StatusCode::NOT_FOUND);
	std::ifstream in(path, std::ios::binary);
	if (!in)
		throw error::Error(http::response::StatusCode::INTERNAL_SERVER_ERROR);
	std::string str;
	in.seekg(0, std::ios::end);
	str.reserve(in.tellg());
	in.seekg(0, std::ios::beg);
	str.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	in.close();
	return str;
}

const std::string Site::getDefaultErrorResponseMessage(int code, http::request::Request& request) noexcept
{
	http::request::RequestLine& line = request.getRequestLine();
	return "Error " + std::to_string(code) + ": " + http::response::StatusCode::getString(code) + "<br/>\n"
		+ line["Method"] + " " + line["Request-URI"] + " " + line["HTTP-Version"];
}

const std::string Site::getResponseMessage(
	http::request::Request & request,
	const std::vector<plugin::Plugin*>& plugins)
{
	std::string body;
	for (plugin::Plugin* p : plugins)
		if (p->getResponseMessage(body, request))
			return body;
	return getDefaultResponseMessage(request);
}

const std::string Site::getErrorResponseMessage(
	int code,
	http::request::Request & request,
	const std::vector<plugin::Plugin*>& plugins)
{
	std::string body;
	for (plugin::Plugin* p : plugins)
		if (p->getErrorResponseMessage(code, body, request))
			return body;

	return getDefaultErrorResponseMessage(code, request);
}