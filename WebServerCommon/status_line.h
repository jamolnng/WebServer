#pragma once
#include "lib_utils.h"
#include "line.h"
namespace webserver
{
	namespace http
	{
		namespace response
		{
			class LIBEXPORT StatusLine :
				public Line
			{
			public:
				StatusLine() noexcept;
			};
		}
	}
}