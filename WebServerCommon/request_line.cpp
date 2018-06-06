#include "request_line.h"

using namespace webserver::http::request;

RequestLine::RequestLine() noexcept :
	Line(
		{
			"Method",
			"Request-URI",
			"HTTP-Version"
		})
{
}