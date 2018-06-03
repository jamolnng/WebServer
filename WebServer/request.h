#pragma once
#include <map>
#include <string>
#include "request_line.h"
#include "general_header.h"
#include "request_header.h"
#include "entity_header.h"
#include "lib_utils.h"

namespace webserver
{
	namespace http
	{
		namespace request
		{
			class LIBEXPORT Request
			{
			public:
				RequestLine requestLine{};
				message::GeneralHeader generalHeader{};
				RequestHeader requestHeader{};
				entity::EntityHeader entityHeader{};

				void clear()
				{
					requestLine.clear();
					generalHeader.clear();
					requestHeader.clear();
					entityHeader.clear();
				}

				void parse(std::vector<std::string>& lines)
				{
					requestLine.parse(lines[0]);
					lines.erase(lines.begin());
					std::map<std::string, std::string> parts;
					std::vector<std::string> split;
					std::string item, val;
					for (const std::string& line : lines)
					{
						split = utils::StringUtils::split(line, ':', 2);
						item = split[0];
						utils::StringUtils::trim(item);
						utils::StringUtils::lower(item);
						if (split.size() == 2)
							val = split[1];
						else
							val = "";
						utils::StringUtils::trim(val);
						parts[item] = val;
					}
					generalHeader.parse(parts);
					requestHeader.parse(parts);
					entityHeader.parse(parts);
				}
			};
		}
	}
}