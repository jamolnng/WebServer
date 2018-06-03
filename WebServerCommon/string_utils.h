#pragma once
#include <strstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
#include "lib_utils.h"


namespace webserver
{
	namespace utils
	{
		class LIBEXPORT StringUtils
		{
		public:
			static void upper(std::string& text);
			static void lower(std::string& text);
			static void triml(std::string& text);
			static void triml(std::string& text, const char* toremove);
			static void trimr(std::string& text);
			static void trimr(std::string& text, const char* toremove);
			static void trim(std::string& text);
			static void trim(std::string& text, const char* toremove);
			static std::vector<std::string> split(const std::string &s, char delim, size_t max = 0);

			template <typename Iter>
			static std::string join(Iter begin, Iter end, std::string const& separator)
			{
				std::ostringstream result;
				if (begin != end)
					result << *begin++;
				while (begin != end)
					result << separator << *begin++;
				return result.str();
			}
		};
	}
}