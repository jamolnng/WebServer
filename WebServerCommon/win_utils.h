#pragma once
#ifdef _WIN32
#include <string>
#include <Windows.h>
namespace webserver
{
	namespace utils
	{
		class WinUtils
		{
		public:
			static std::string GetLastErrorAsString();
		private:
			WinUtils() {};
		};
	}
}
#endif