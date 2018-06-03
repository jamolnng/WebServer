#pragma once
#include <string>
#include "request.h"
#include "lib_utils.h"

namespace webserver
{
	namespace http
	{
		namespace request
		{
			class LIBEXPORT RequestParser
			{
			public:
				RequestParser();
				~RequestParser();

				void parse(std::string part);
				void clear();
				const bool isDone() const;
				const Request get() const;

				std::string requestStr{};
			private:
				Request request{};
				bool done{ false };
			};
		}
	}
}