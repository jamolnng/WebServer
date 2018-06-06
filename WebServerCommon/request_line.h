#pragma once
#include <string>
#include "line.h"
#include "lib_utils.h"
#include "string_utils.h"

namespace webserver
{
	namespace http
	{
		namespace request
		{
			class LIBEXPORT RequestLine :
				public Line
			{
			public:
				RequestLine() noexcept;
			};
		}
	}
}