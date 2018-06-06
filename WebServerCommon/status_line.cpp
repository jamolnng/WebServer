#include "status_line.h"

using namespace webserver::http::response;

StatusLine::StatusLine() noexcept :
	Line(
		{
			"HTTP-Version",
			"Status-Code",
			"Reason-Phrase"
		})
{
}