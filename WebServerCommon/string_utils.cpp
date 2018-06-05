#include "string_utils.h"

using namespace webserver::utils;

void StringUtils::upper(std::string& text)
{
	std::transform(text.begin(), text.end(), text.begin(), toupper);
}

void StringUtils::lower(std::string& text)
{
	std::transform(text.begin(), text.end(), text.begin(), tolower);
}

void StringUtils::triml(std::string& text)
{
	if (!text.empty())
	{
		std::string::iterator pos = text.begin();
		while (pos != text.end() && isspace(*pos)) pos++;

		text.erase(text.begin(), pos);
	}
}

void StringUtils::triml(std::string& text, const char* toremove)
{
	if (!text.empty())
	{
		std::string::size_type pos = text.find_first_not_of(toremove);
		if (std::string::npos != pos) text.erase(0, pos);
		else text.clear();
	}
}

void StringUtils::trimr(std::string& text)
{
	if (!text.empty())
	{
		std::string::iterator pos = text.end() - 1;
		while (pos != text.begin() && isspace(*pos)) pos--;

		text.erase(pos + 1, text.end());
	}
}

void StringUtils::trimr(std::string& text, const char* toremove)
{
	if (!text.empty())
	{
		std::string::size_type pos = text.find_last_not_of(toremove);
		if (std::string::npos != pos) text.erase(pos + 1);
		else text.clear();
	}
}

void StringUtils::trim(std::string& text)
{
	triml(text);
	trimr(text);
}

void StringUtils::trim(std::string& text, const char* toremove)
{
	triml(text, toremove);
	trimr(text, toremove);
}

std::vector<std::string> StringUtils::split(const std::string &s, char delim, size_t max)
{
	std::vector<std::string> all;
	std::stringstream ss(s);
	std::string line;
	while (std::getline(ss, line, delim))
	{
		trim(line);
		all.push_back(line);
	}
	if (max == 0)
		max = all.size();
	std::vector<std::string> elems;
	if (all.size() > max)
	{
		elems.insert(elems.end(), all.begin(), all.begin() + max - 1);
		std::string last;
		for (auto it = all.begin() + max - 1; it != all.end(); ++it)
			last += *it + std::string(1, delim);
		last = last.substr(0, last.size() - 1);
		trim(last);
		elems.push_back(last);
	}
	else
		elems = all;
	return elems;
}

std::string StringUtils::strerror(int errnum)
{
	return std::string(std::strerror(errnum));
}