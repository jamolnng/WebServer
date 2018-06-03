#include "request_line.h"

using namespace webserver::http::request;

RequestLine::RequestLine() :
	Line(
		{
			"Method",
			"Request-URI",
			"HTTP-Version"
		})
{
}