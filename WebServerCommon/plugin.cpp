#include "plugin.h"

using namespace webserver::plugin;

bool Plugin::modifyRequestHeader(webserver::http::request::Request & request)
{
	return false;
}

bool Plugin::getResponseMessage(std::string & body, const webserver::http::request::Request& request)
{
	return false;
}

bool Plugin::getErrorResponseMessage(int code, std::string & body, const webserver::http::request::Request & request)
{
	return false;
}

bool Plugin::getReponseHeader(webserver::http::response::Response & response)
{
	return false;
}
