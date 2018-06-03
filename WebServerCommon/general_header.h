#pragma once
#include <iostream>
#include <map>
#include <string>
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

				void clear();
				void parse(std::map<std::string, std::string>& parts);
			};
		}
	}
}