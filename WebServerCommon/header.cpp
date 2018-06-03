#include "header.h"

using namespace webserver::http;

Header::Header(std::set<std::string> valid) :
	valid(valid)
{
}

const std::map<std::string, std::string>& Header::operator*() const
{
	return items;
}

std::string const& Header::operator[](std::string item) const
{
	return items.at(item);
}

std::string& Header::operator[](std::string item)
{
	return items[item];
}

void Header::clear()
{
	items.clear();
}

void Header::parse(std::map<std::string, std::string>& parts)
{
	for (auto it = parts.begin(); it != parts.end(); )
	{
		auto p = *it;
		if (isValid(p.first))
		{
			items[p.first] = p.second;
			parts.erase(it++);
		}
		else
			++it;
	}
}

bool Header::has(std::string item)
{
	return items.find(item) != items.end();
}

bool Header::isValid(const std::string& val)
{
	return Header::inContainer<std::set<std::string>>(val, valid);
}