#include "line.h"
#include "string_utils.h"
#include <sstream>

using namespace webserver::http;

Line::Line(std::vector<std::string> names) :
	names(names)
{
}

const std::map<std::string, std::string>& Line::operator*() const
{
	return items;
}

std::string& Line::operator[](const std::string& item)
{
	return items.insert(std::make_pair(item, std::string())).first->second;
}

std::string& Line::operator[](std::string&& item)
{
	return items.try_emplace(std::move(item)).first->second;
}

void Line::clear()
{
	items.clear();
}

void Line::parse(const std::string& line)
{
	std::vector<std::string> parts = utils::StringUtils::split(line, ' ', names.size());
	for (size_t i = 0; i < names.size(); i++)
		items[names[i]] = parts[i];
}

std::string Line::build()
{
	std::stringstream oss;
	for (auto& n : names)
		if(isValid(n))
			oss << items[n] << " ";
	return oss.str().substr(0, oss.str().size() - 1);
}

bool Line::isValid(const std::string& val)
{
	return Line::inContainer<std::vector<std::string>>(val, names);
}