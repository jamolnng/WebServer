#pragma once
#include <string>
#include <iostream>
#include "lib_utils.h"
#include "string_utils.h"

namespace webserver
{
	namespace http
	{
		namespace message
		{
			class LIBEXPORT GeneralHeader
			{
			public:
				std::string cacheControl{};
				std::string connection{};
				std::string date{};
				std::string pragma{};
				std::string trailer{};
				std::string transferEncoding{};
				std::string upgrade{};
				std::string via{};
				std::string warning{};

				void clear()
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

				void parse(std::map<std::string, std::string>& parts)
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
			};
		}
	}
}