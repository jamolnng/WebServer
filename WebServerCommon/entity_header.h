#pragma once
#include <map>
#include <string>
#include "header.h"
#include "lib_utils.h"

namespace webserver
{
	namespace http
	{
		namespace entity
		{
			class LIBEXPORT EntityHeader :
				public Header
			{
			public:
				EntityHeader();

				void parse(std::map<std::string, std::string>& parts) override;
			};
		}
	}
}