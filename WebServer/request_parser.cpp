#include "request_parser.h"
#include "string_utils.h"

using namespace webserver::http::request;

RequestParser::RequestParser() noexcept
{
}

RequestParser::~RequestParser()
{
}

void RequestParser::parse(std::string part)
{
	requestStr += part;
	if (requestStr.find("\r\n\r\n") != std::string::npos)
		done = true;
	if (done)
	{
		requestStr = requestStr.substr(0, requestStr.size() - 4);
		std::vector<std::string> lines = utils::StringUtils::split(requestStr, '\n');
		request.parse(lines);
	}
}

void RequestParser::clear()
{
	request.clear();
	requestStr.clear();
	done = false;
}

const bool RequestParser::isDone() const
{
	return done;
}

const Request RequestParser::get() const
{
	return request;
}