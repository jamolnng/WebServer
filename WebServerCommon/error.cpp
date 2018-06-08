#include "error.h"
#include "status_code.h"

using namespace webserver::error;
using webserver::http::response::StatusCode;

Error::Error(int code) :
	message(StatusCode::getString(code)),
	status(code)
{
}

const char * webserver::error::Error::what() throw()
{
	return message.c_str();
}

const int Error::code()
{
	return status;
}