#include "error.h"
#include "status_code.h"

using webserver::http::error::Error;
using webserver::http::response::StatusCode;

Error::Error(int code, std::string additional)
    : status(code), message(StatusCode::getString(code) + (additional.empty() ? "" : ": " + additional)) {}

const char* Error::what() const throw() { return message.c_str(); }

const int Error::code() const { return status; }
