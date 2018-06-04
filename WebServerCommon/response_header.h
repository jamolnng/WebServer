#pragma once
#include "header.h"
namespace webserver
{
	namespace http
	{
		namespace response
		{
			class ResponseHeader :
				public Header
			{
			public:
				ResponseHeader();
			};
		}
	}
}