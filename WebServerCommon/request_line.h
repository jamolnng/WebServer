#pragma once
#include <string>
#include "lib_utils.h"
#include "string_utils.h"

namespace webserver
{
	namespace http
	{
		namespace request
		{
			class LIBEXPORT RequestLine
			{
			public:
				std::string method{};
				std::string requestURI{};
				std::string httpVersion{};

				void clear();
				void parse(const std::string& line);
			};
		}
	}
}