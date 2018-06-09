/*
Copyright 2018 Jesse Laning
*/

#include "response_header.h"

using webserver::http::response::ResponseHeader;

ResponseHeader::ResponseHeader() noexcept
    : Header({"Accept-Ranges", "Age", "ETag", "Location", "Proxy-Authenticate",
              "Retry-After", "Server", "Vary", "WWW-Authenticate"}) {}
