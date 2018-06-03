#include "request_header.h"

using namespace webserver::http::request;

void RequestHeader::clear()
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

void RequestHeader::parse(std::map<std::string, std::string>& parts)
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