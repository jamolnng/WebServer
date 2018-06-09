/*
Copyright 2018 Jesse Laning
*/

#include "error.h"
#include "status_code.h"

using webserver::http::error::Error;
using webserver::http::response::StatusCode;

Error::Error(int code) : message(StatusCode::getString(code)), status(code) {}

const char* Error::what() throw() { return message.c_str(); }

const int Error::code() { return status; }
