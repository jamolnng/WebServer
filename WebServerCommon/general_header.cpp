#include "general_header.h"

using namespace webserver::http::message;

void GeneralHeader::clear()
{
	cacheControl.clear();
	connection.clear();
	date.clear();
	pragma.clear();
	trailer.clear();
	transferEncoding.clear();
	upgrade.clear();
	via.clear();
	warning.clear();
}

void GeneralHeader::parse(std::map<std::string, std::string>& parts)
{
	for (auto it = parts.begin(); it != parts.end(); )
	{
		auto p = *it;
		if (p.first == "cache-control")
		{
			cacheControl = p.second;
			parts.erase(it++);
		}
		else if (p.first == "connection")
		{
			connection = p.second;
			utils::StringUtils::lower(connection);
			parts.erase(it++);
		}
		else if (p.first == "date")
		{
			date = p.second;
			parts.erase(it++);
		}
		else if (p.first == "pragma")
		{
			pragma = p.second;
			parts.erase(it++);
		}
		else if (p.first == "trailer")
		{
			trailer = p.second;
			parts.erase(it++);
		}
		else if (p.first == "transfer-encoding")
		{
			transferEncoding = p.second;
			parts.erase(it++);
		}
		else if (p.first == "upgrade")
		{
			upgrade = p.second;
			parts.erase(it++);
		}
		else if (p.first == "via")
		{
			via = p.second;
			parts.erase(it++);
		}
		else if (p.first == "warning")
		{
			warning = p.second;
			parts.erase(it++);
		}
		else
		{
			++it;
		}
	}
}