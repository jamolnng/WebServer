#pragma once
#include <map>
#include <string>
#include "header.h"
#include "lib_utils.h"
#include "string_utils.h"

namespace webserver
{
	namespace http
	{
		namespace request
		{
			class LIBEXPORT RequestHeader :
				public Header
			{
			public:
				RequestHeader() noexcept;
			};
		}
	}
}