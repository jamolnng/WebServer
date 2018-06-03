#pragma once
#include <strstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <locale>
#include <codecvt>
#include <iterator>
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

		private:
			template<typename Container>
			static void _split(const std::string &s, char delim, Container result, size_t max = 0)
			{
				if (max < 1)
					max = std::count(s.begin(), s.end(), delim);
				std::stringstream ss(s);
				std::string item;
				std::ostringstream os;
				size_t count = 0;
				while (std::getline(ss, item, delim))
				{
					if (count < max - 1)
						*(result++) = item;
					else
						os << item << delim;
					count++;
				}
				if (!os.str().empty())
					*(result++) = os.str().substr(0, os.str().size() - 1);
			}
		};
	}
}