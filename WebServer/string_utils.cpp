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
	//if (isspace(delim))
	//{
	//	std::istringstream iss(s);
	//	return std::vector<std::string>{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
	//}
	std::vector<std::string> elems;
	_split(s, delim, std::back_inserter(elems), max);
	return elems;
}