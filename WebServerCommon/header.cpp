#include "header.h"
#include <sstream>
#include <iostream>

using namespace webserver::http;

Header::Header(std::set<std::string> valid) :
	valid(valid)
{
}

const std::map<std::string, std::string>& Header::operator*() const
{
	return items;
}

std::string& Header::operator[](const std::string& item)
{
	return items.insert(std::make_pair(item, std::string())).first->second;
}

std::string& Header::operator[](std::string&& item)
{
	return items.try_emplace(std::move(item)).first->second;
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

bool Header::has(const std::string& item)
{
	return items.find(item) != items.end();
}

bool Header::isValid(const std::string& val)
{
	return Header::inContainer<std::set<std::string>>(val, valid);
}

std::string Header::build()
{
	std::ostringstream oss;
	for (auto& p : items)
		if(isValid(p.first))
			oss << p.first << ": " << p.second << std::endl;
	return oss.str();
}