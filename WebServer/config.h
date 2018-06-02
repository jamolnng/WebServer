#pragma once
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "string_utils.h"

namespace webserver
{
	namespace config
	{
		class Config
		{
		public:
			Config(std::string file)
			{
				loadConfig(file);
			}

			void loadConfig(std::string file)
			{
				std::ifstream in(file, std::ios::binary);
				if (in)
				{
					std::string line;
					std::string item;
					std::string val;
					std::vector<std::string> s;
					while (getline(in, line))
					{
						utils::StringUtils::trim(line);
						if (line.empty())
							continue;
						if (line[0] == '#')
							continue;
						s = utils::StringUtils::split(line, '=', 2);
						item = s[0];
						utils::StringUtils::trim(item);
						if (s.size() == 2)
							val = s[1];
						else
							val = "true";
						utils::StringUtils::trim(val);
						config[item] = val;
					}
					in.close();
				}
			}

			inline bool hasItem(std::string item)
			{
				return config.find(item) != config.end();
			}

			inline bool getBool(std::string item)
			{
				return config[item] == "true";
			}

			inline double getDouble(std::string item)
			{
				return std::stod(config[item]);
			}

			inline int getInt(std::string item)
			{
				return std::stoi(config[item]);
			}

			inline std::string getString(std::string item)
			{
				return config[item];
			}

			inline std::string& operator[](std::string item)
			{
				return config[item];
			}

		private:
			std::map<std::string, std::string> config;
		};
	}
}