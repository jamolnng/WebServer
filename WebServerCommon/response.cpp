#include "response.h"
#include <sstream>

using namespace webserver::http::response;

void Response::clear()
{
	statusLine.clear();
	generalHeader.clear();
	responseHeader.clear();
	entityHeader.clear();
}

std::string Response::build()
{
	std::ostringstream oss;
	oss << statusLine.build() << std::endl;
	oss << generalHeader.build();
	oss << responseHeader.build();
	oss << entityHeader.build();
	oss << std::endl;
	return oss.str();
}

StatusLine & webserver::http::response::Response::getStatusLine()
{
	return statusLine;
}

webserver::http::message::GeneralHeader & webserver::http::response::Response::getGeneralHeader()
{
	return generalHeader;
}

ResponseHeader & webserver::http::response::Response::getResponseHeader()
{
	return responseHeader;
}

webserver::http::entity::EntityHeader & webserver::http::response::Response::getEntityHeader()
{
	return entityHeader;
}