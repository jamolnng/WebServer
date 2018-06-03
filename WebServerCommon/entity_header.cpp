#include "entity_header.h"
#include <iostream>

using namespace webserver::http::entity;

EntityHeader::EntityHeader() :
	Header(
		{
			"Allow",
			"Content-Encoding",
			"Content-Language",
			"Content-Length",
			"Content-Location",
			"Content-MD5",
			"Content-Range",
			"Content-Type",
			"Expires",
			"Last-Modified"
		})
{
}

void EntityHeader::parse(std::map<std::string, std::string>& parts)
{
	items.insert(parts.begin(), parts.end());
}