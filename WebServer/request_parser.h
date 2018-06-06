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
			class RequestParser
			{
			public:
				RequestParser() noexcept;
				~RequestParser();

				void parse(std::string part);
				void clear();
				const bool isDone() const;
				const Request get() const;

			private:
				std::string requestStr{};
				Request request{};
				bool done{ false };
			};
		}
	}
}