#include "request_line.h"

using namespace webserver::http::request;

void RequestLine::clear()
{
	method.clear();
	requestURI.clear();
	httpVersion.clear();
}

void RequestLine::parse(const std::string& line)
{
	std::vector<std::string> parts = utils::StringUtils::split(line, ' ');
	if (parts.size() == 3)
	{
		method = parts[0];
		requestURI = parts[1];
		httpVersion = parts[2];
	}
}