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

				void clear();
				void parse(std::vector<std::string>& lines);
			};
		}
	}
}