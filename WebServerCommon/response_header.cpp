#include "response_header.h"

using namespace webserver::http::response;

ResponseHeader::ResponseHeader() :
	Header(
		{
			"Accept-Ranges",
			"Age",
			"ETag",
			"Location",
			"Proxy-Authenticate",
			"Retry-After",
			"Server",
			"Vary",
			"WWW-Authenticate"
		})
{
}