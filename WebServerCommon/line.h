#pragma once
#include <map>
#include <string>
#include <vector>
#include "lib_utils.h"
namespace webserver
{
	namespace http
	{
		class LIBEXPORT Line
		{
		public:
			std::string& operator[](const std::string& item);
			std::string& operator[](std::string&& item);
			const std::map<std::string, std::string>& operator*() const;
			void clear();
			void parse(const std::string& line);
			virtual std::string build();

		protected:
			std::vector<std::string> names;
			std::map<std::string, std::string> items;

			Line(std::vector<std::string> names);

			bool isValid(const std::string& val);

			template<typename Container>
			static bool inContainer(const std::string val, const Container& cont)
			{
				return std::find(cont.begin(), cont.end(), val) != cont.end();
			}
		};
	}
}