#pragma once
#include <string>
#include <fstream>
#include <map>
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

			void loadConfig(std::filesystem::path file);
			inline bool hasItem(std::string item);
			inline bool getBool(std::string item);
			inline double getDouble(std::string item);
			inline int getInt(std::string item);
			inline std::string getString(std::string item);
			std::string& operator[](std::string item);

		private:
			std::map<std::string, std::string> config;
		};
	}
}