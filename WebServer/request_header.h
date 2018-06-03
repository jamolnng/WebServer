#pragma once
#include <string>
#include "lib_utils.h"
#include "string_utils.h"

namespace webserver
{
	namespace http
	{
		namespace request
		{
			class RequestHeader
			{
			public:
				std::string accept{};
				std::string acceptCharset{};
				std::string acceptEncoding{};
				std::string acceptLanguage{};
				std::string authorization{};
				std::string except{};
				std::string from{};
				std::string host{};
				std::string ifMatch{};
				std::string ifModifiedSince{};
				std::string ifNoneMatch{};
				std::string ifRange{};
				std::string ifUnmodifiedSince{};
				std::string maxForwards{};
				std::string proxyAuthorization{};
				std::string range{};
				std::string referer{};
				std::string	te{};
				std::string userAgent{};

				void clear()
				{
					accept.clear();
					acceptCharset.clear();
					acceptEncoding.clear();
					acceptLanguage.clear();
					authorization.clear();
					except.clear();
					from.clear();
					host.clear();
					ifMatch.clear();
					ifModifiedSince.clear();
					ifNoneMatch.clear();
					ifRange.clear();
					ifUnmodifiedSince.clear();
					maxForwards.clear();
					proxyAuthorization.clear();
					range.clear();
					referer.clear();
					te.clear();
					userAgent.clear();
				}

				void parse(std::map<std::string, std::string>& parts)
				{
					for (auto it = parts.begin(); it != parts.end(); )
					{
						auto p = *it;
						if (p.first == "accept")
						{
							accept = p.second;
							parts.erase(it++);
						}
						else if (p.first == "accept-charset")
						{
							acceptCharset = p.second;
							parts.erase(it++);
						}
						else if (p.first == "accept-encoding")
						{
							acceptEncoding = p.second;
							parts.erase(it++);
						}
						else if (p.first == "accept-language")
						{
							acceptLanguage = p.second;
							parts.erase(it++);
						}
						else if (p.first == "authorization")
						{
							authorization = p.second;
							parts.erase(it++);
						}
						else if (p.first == "except")
						{
							except = p.second;
							parts.erase(it++);
						}
						else if (p.first == "from")
						{
							from = p.second;
							parts.erase(it++);
						}
						else if (p.first == "host")
						{
							host = p.second;
							parts.erase(it++);
						}
						else if (p.first == "if-match")
						{
							ifMatch = p.second;
							parts.erase(it++);
						}
						else if (p.first == "if-modified-since")
						{
							ifModifiedSince = p.second;
							parts.erase(it++);
						}
						else if (p.first == "if-none-match")
						{
							ifNoneMatch = p.second;
							parts.erase(it++);
						}
						else if (p.first == "if-range")
						{
							ifRange = p.second;
							parts.erase(it++);
						}
						else if (p.first == "if-unmodified-since")
						{
							ifUnmodifiedSince = p.second;
							parts.erase(it++);
						}
						else if (p.first == "max-forwards")
						{
							maxForwards = p.second;
							parts.erase(it++);
						}
						else if (p.first == "proxy-authorization")
						{
							proxyAuthorization = p.second;
							parts.erase(it++);
						}
						else if (p.first == "range")
						{
							range = p.second;
							parts.erase(it++);
						}
						else if (p.first == "referer")
						{
							referer = p.second;
							parts.erase(it++);
						}
						else if (p.first == "te")
						{
							te = p.second;
							parts.erase(it++);
						}
						else if (p.first == "user-agent")
						{
							userAgent = p.second;
							parts.erase(it++);
						}
						else
						{
							++it;
						}
					}
				}
			};
		}
	}
}