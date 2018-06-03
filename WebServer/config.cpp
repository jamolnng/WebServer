#include "config.h"
#include <iostream>

using namespace webserver::config;

Config::Config(std::filesystem::path file)
{
	loadConfig(file);
}

void Config::loadConfig(std::filesystem::path file)
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
	if (!hasItem("plugins"))
		config["plugins"] = "plugins";
	std::filesystem::path p(config["plugins"]);
	if (p.is_relative())
		config["plugins"] = (file.parent_path() / p).generic_string();
}

inline bool Config::hasItem(std::string item)
{
	return config.find(item) != config.end();
}

inline bool Config::getBool(std::string item)
{
	return config[item] == "true";
}

inline double Config::getDouble(std::string item)
{
	return std::stod(config[item]);
}

inline int Config::getInt(std::string item)
{
	return std::stoi(config[item]);
}

inline std::string Config::getString(std::string item)
{
	return config[item];
}

std::string& Config::operator[](std::string item)
{
	return config[item];
}