#include "status_code.h"
#include <map>

using namespace webserver::http::response;

static std::map<int, std::string> map =
{
	{ StatusCode::CONTINUE, "Continue" },
	{ StatusCode::SWITCHING_PROTOCOLS, "Switching Protocols" },
	{ StatusCode::OK, "OK" },
	{ StatusCode::CREATED, "Created" },
	{ StatusCode::ACCEPTED, "Accepted" },
	{ StatusCode::NON_AUTHORITATIVE_INFORMATION, "Non-Authoritative Information" },
	{ StatusCode::NO_CONTENT, "No Content" },
	{ StatusCode::RESET_CONTENT, "Reset Content" },
	{ StatusCode::PARTIAL_CONTENT, "Partial Content" },
	{ StatusCode::MULTIPLE_CHOICES, "Multiple Choices" },
	{ StatusCode::MOVED_PERMANENTLY, "Moved Permanently" },
	{ StatusCode::FOUND, "Found" },
	{ StatusCode::SEE_OTHER, "See Other" },
	{ StatusCode::NOT_MODIFIED, "Not Modified" },
	{ StatusCode::USE_PROXY, "Use Proxy" },
	{ StatusCode::TEMPORARY_REDIRECT, "Temporary Redirect" },
	{ StatusCode::BAD_REQUEST, "Bad Request" },
	{ StatusCode::UNAUTHORIZED, "Unauthorized" },
	{ StatusCode::PAYMENT_REQUIRED, "Payment Required" },
	{ StatusCode::FORBIDDEN, "Forbidden" },
	{ StatusCode::NOT_FOUND, "Not Found" },
	{ StatusCode::METHOD_NOT_ALLOWED, "Method Not Allowed" },
	{ StatusCode::NOT_ACCEPTABLE, "Not Acceptable" },
	{ StatusCode::PROXY_AUTHENTICATION_REQUIRED, "Proxy Authentication Required" },
	{ StatusCode::REQUEST_TIMEOUT, "Request Timeout" },
	{ StatusCode::CONFLICT, "Conflict" },
	{ StatusCode::GONE, "Gone" },
	{ StatusCode::LENGTH_REQUIRED, "Length Required" },
	{ StatusCode::PRECONDITION_FAILED, "Precondition Failed" },
	{ StatusCode::REQUEST_ENTITY_TOO_LARGE, "Request Entity Too Large" },
	{ StatusCode::REQUEST_URI_TOO_LARGE, "Request-URI Too Large" },
	{ StatusCode::UNSUPPORTED_MEDIA_TYPE, "Unsupported Media Type" },
	{ StatusCode::REQUEST_RANGE_NOT_SATISFIABLE, "Request Range Not Satisfiable" },
	{ StatusCode::EXPECTATION_FAILED, "Expectation Failed" },
	{ StatusCode::INTERNAL_SERVER_ERROR, "Internal Server Error" },
	{ StatusCode::NOT_IMPLEMENTED, "Not Implemented" },
	{ StatusCode::BAD_GATEWAY, "Bad Gateway" },
	{ StatusCode::SERVICE_UNAVAILABLE, "Service Unavailable" },
	{ StatusCode::GATEWAY_TIMEOUT, "Gateway Timeout" },
	{ StatusCode::HTTP_VERSION_NOT_SUPPORTED, "HTTP Version Not Supported" }
};


std::string StatusCode::getString(int code)
{
	if(map.find(code) != map.end())
		return map[code];
	return "Unknown";
}

void StatusCode::insert(int code, const std::string& str)
{
	map[code] = str;
}