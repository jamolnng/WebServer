#pragma once
#include <string>
#include <fstream>
#include <map>
#include <type_traits>
#include <vector>
#include "string_utils.h"
#include "lib_utils.h"
#include "file_utils.h"

namespace webserver
{
	namespace config
	{
		class LIBEXPORT Config
		{
		public:
			Config(std::filesystem::path file);
			Config(std::filesystem::path file, std::map<std::string, std::string> defaults);

			void load(std::filesystem::path file);
			inline bool has(std::string item);
			std::string& operator[](const std::string& item);
			std::string& operator[](std::string&& item);

			template<typename T> T get(const std::string& item);

			template<>
			double get<double>(const std::string& item)
			{
				return std::stod(config[item]);
			}

			template<>
			int get<int>(const std::string& item)
			{
				return std::stoi(config[item]);
			}

			template<>
			std::string get<std::string>(const std::string& item)
			{
				return config[item];
			}

		private:
			std::map<std::string, std::string> config;
		};
	}
}