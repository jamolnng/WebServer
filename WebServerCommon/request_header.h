#pragma once
#include <map>
#include <string>
#include "lib_utils.h"
#include "string_utils.h"

namespace webserver
{
	namespace http
	{
		namespace request
		{
			class LIBEXPORT RequestHeader
			{
			public:
				std::string accept{};
				std::string acceptCharset{};
				std::string acceptEncoding{};
				std::string acceptLanguage{};
				std::string authorization{};
				std::string except{};
				std::string from{};
				std::string host{};
				std::string ifMatch{};
				std::string ifModifiedSince{};
				std::string ifNoneMatch{};
				std::string ifRange{};
				std::string ifUnmodifiedSince{};
				std::string maxForwards{};
				std::string proxyAuthorization{};
				std::string range{};
				std::string referer{};
				std::string	te{};
				std::string userAgent{};

				void clear();
				void parse(std::map<std::string, std::string>& parts);
			};
		}
	}
}