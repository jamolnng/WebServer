#pragma once
#include <string>
#include "lib_utils.h"
#include "string_utils.h"

namespace webserver
{
	namespace http
	{
		class LIBEXPORT RequestLine
		{
		public:
			std::string method{};
			std::string requestURI{};
			std::string httpVersion{};

			void clear()
			{
				method.clear();
				requestURI.clear();
				httpVersion.clear();
			}

			void parse(const std::string& line)
			{
				std::vector<std::string> parts = utils::StringUtils::split(line, ' ');
				if (parts.size() == 3)
				{
					method = parts[0];
					requestURI = parts[1];
					httpVersion = parts[2];
				}
			}
		};
	}
}