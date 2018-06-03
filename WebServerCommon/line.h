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
			std::string const& operator[](std::string item) const;
			std::string& operator[](std::string item);
			const std::map<std::string, std::string>& operator*() const;
			void clear();
			void parse(const std::string& line);

		protected:
			std::vector<std::string> names;
			std::map<std::string, std::string> items;

			Line(std::vector<std::string> names);
		};
	}
}