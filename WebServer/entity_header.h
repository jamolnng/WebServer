#pragma once
#include <map>
#include <string>
#include "lib_utils.h"

namespace webserver
{
	namespace http
	{
		namespace entity
		{
			class EntityHeader
			{
			public:
				std::string allow{};
				std::string contentEncoding{};
				std::string contentLanguage{};
				unsigned int contentLength{ 0 };
				std::string contentLocation{};
				std::string contentMD5{};
				std::string contentRange{};
				std::string contentType{};
				std::string expires{};
				std::string lastModified{};
				std::map<std::string, std::string> extensions{};

				void clear()
				{
					allow.clear();
					contentEncoding.clear();
					contentLanguage.clear();
					contentLength = 0;
					contentLocation.clear();
					contentMD5.clear();
					contentRange.clear();
					contentType.clear();
					expires.clear();
					lastModified.clear();
					extensions.clear();
				}

				void parse(std::map<std::string, std::string>& parts)
				{
					for (auto it = parts.begin(); it != parts.end(); )
					{
						auto p = *it;
						if (p.first == "allow")
						{
							allow = p.second;
							parts.erase(it++);
						}
						else if (p.first == "content-encoding")
						{
							contentEncoding = p.second;
							parts.erase(it++);
						}
						else if (p.first == "content-language")
						{
							contentLanguage = p.second;
							parts.erase(it++);
						}
						else if (p.first == "content-length")
						{
							contentLength = std::stoi(p.second);
							parts.erase(it++);
						}
						else if (p.first == "content-location")
						{
							contentLocation = p.second;
							parts.erase(it++);
						}
						else if (p.first == "content-md5")
						{
							contentMD5 = p.second;
							parts.erase(it++);
						}
						else if (p.first == "content-range")
						{
							contentRange = p.second;
							parts.erase(it++);
						}
						else if (p.first == "content-type")
						{
							contentType = p.second;
							parts.erase(it++);
						}
						else if (p.first == "expires")
						{
							expires = p.second;
							parts.erase(it++);
						}
						else if (p.first == "last-modified")
						{
							contentType = p.second;
							parts.erase(it++);
						}
						else
						{
							extensions[p.first] = p.second;
							++it;
						}
					}
				}
			};
		}
	}
}