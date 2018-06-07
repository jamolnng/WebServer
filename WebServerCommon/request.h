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
				Request() = default;

				void clear();
				void parse(std::vector<std::string>& lines);

				RequestLine& getRequestLine();
				message::GeneralHeader& getGeneralHeader();
				RequestHeader& getRequestHeader();
				entity::EntityHeader& getEntityHeader();
			
			private:
				RequestLine requestLine{};
				message::GeneralHeader generalHeader{};
				RequestHeader requestHeader{};
				entity::EntityHeader entityHeader{};
			};
		}
	}
}