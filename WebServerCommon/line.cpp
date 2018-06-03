#include "line.h"
#include "string_utils.h"

using namespace webserver::http;

Line::Line(std::vector<std::string> names) :
	names(names)
{
}

const std::map<std::string, std::string>& Line::operator*() const
{
	return items;
}

std::string const& Line::operator[](std::string item) const
{
	return items.at(item);
}

std::string& Line::operator[](std::string item)
{
	return items[item];
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