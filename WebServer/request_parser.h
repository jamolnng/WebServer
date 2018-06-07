#pragma once
#include <string>
#include <sstream>
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
				RequestParser() noexcept = default;

				void parse(const std::string& str);
				void clear();
				const bool isDone() const;
				const Request& get() const;
				bool operator!();
				RequestParser& operator<<(const std::string& str);

			private:
				std::string buf{};
				Request request{};
				size_t offset{ 0 };
				bool done{ false };
			};

		}
	}
}