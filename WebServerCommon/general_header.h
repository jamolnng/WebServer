#pragma once
#include <iostream>
#include <map>
#include <string>
#include "header.h"
#include "lib_utils.h"
#include "string_utils.h"

namespace webserver
{
	namespace http
	{
		namespace message
		{
			class LIBEXPORT GeneralHeader :
				public Header
			{
			public:
				GeneralHeader();
			};
		}
	}
}