#include "request_parser.h"
#include "string_utils.h"

using namespace webserver::http::request;

void RequestParser::parse(const std::string& str)
{
	buf += str;
	size_t end = buf.find("\r\n\r\n");
	if (end != std::string::npos)
	{
		std::vector<std::string> lines = utils::StringUtils::split(buf.substr(0, end), '\n');
		request.parse(lines);
		done = true;
	}
}

void RequestParser::clear()
{
	request.clear();
	buf.clear();
	done = false;
}

const bool RequestParser::isDone() const
{
	return done;
}

const Request& RequestParser::get() const
{
	return request;
}

bool RequestParser::operator!()
{
	return !done;
}

RequestParser& RequestParser::operator<<(const std::string& str)
{
	parse(str);
	return *this;
}