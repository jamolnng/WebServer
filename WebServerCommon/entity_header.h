#pragma once
#include <map>
#include <string>
#include "lib_utils.h"

namespace webserver
{
	namespace http
	{
		namespace entity
		{
			class LIBEXPORT EntityHeader
			{
			public:
				std::string allow{};
				std::string contentEncoding{};
				std::string contentLanguage{};
				unsigned int contentLength{ 0 };
				std::string contentLocation{};
				std::string contentMD5{};
				std::string contentRange{};
				std::string contentType{};
				std::string expires{};
				std::string lastModified{};
				std::map<std::string, std::string> extensions{};

				void clear();
				void parse(std::map<std::string, std::string>& parts);
			};
		}
	}
}