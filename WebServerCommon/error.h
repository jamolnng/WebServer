#pragma once
#include <stdexcept>
#include "lib_utils.h"

namespace webserver
{
	namespace error
	{
		class LIBEXPORT Error :
			public std::exception
		{
		public:
			explicit Error(int code);
			const char* what() throw();
			const int code();

		private:
			Error() = delete;
			std::string message;
			int status;
		};
	}
}