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


namespace webserver
{
	namespace utils
	{
		class StringUtils
		{
		public:
			static inline void make_upper(std::string& text)
			{
				std::transform(text.begin(), text.end(), text.begin(), toupper);
			}

			static inline void make_lower(std::string& text)
			{
				std::transform(text.begin(), text.end(), text.begin(), tolower);
			}

			static void trim_left(std::string& text)
			{
				if (!text.empty())
				{
					std::string::iterator pos = text.begin();
					while (pos != text.end() && isspace(*pos)) pos++;

					text.erase(text.begin(), pos);
				}
			}

			static void trim_left(std::string& text, const char* toremove)
			{
				if (!text.empty())
				{
					std::string::size_type pos = text.find_first_not_of(toremove);
					if (std::string::npos != pos) text.erase(0, pos);
					else text.clear();
				}
			}

			static void trim_right(std::string& text)
			{
				if (!text.empty())
				{
					std::string::iterator pos = text.end() - 1;
					while (pos != text.begin() && isspace(*pos)) pos--;

					text.erase(pos + 1, text.end());
				}
			}

			static void trim_right(std::string& text, const char* toremove)
			{
				if (!text.empty())
				{
					std::string::size_type pos = text.find_last_not_of(toremove);
					if (std::string::npos != pos) text.erase(pos + 1);
					else text.clear();
				}
			}

			static inline void trim(std::string& text)
			{
				trim_right(text);
				trim_left(text);
			}

			static std::vector<std::string> split(const std::string &s, char delim, size_t max = 0)
			{
				if (isspace(delim))
				{
					std::istringstream iss(s);
					return std::vector<std::string>{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
				}
				std::vector<std::string> elems;
				_split(s, delim, std::back_inserter(elems), max);
				return elems;
			}

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