/*
Copyright 2018 Jesse Laning
*/

#include "request_line.h"

using webserver::http::request::RequestLine;

RequestLine::RequestLine() noexcept
    : Line({"Method", "Request-URI", "HTTP-Version"}) {}
