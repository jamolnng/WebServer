#include "general_header.h"

using namespace webserver::http::message;

GeneralHeader::GeneralHeader() :
	Header(
		{
			"Cache-Control",
			"Connection",
			"Date",
			"Pragma",
			"Trailer",
			"Transfer-Encoding",
			"Upgrade",
			"Via",
			"Warning"
		})
{
}