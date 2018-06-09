/*
Copyright 2018 Jesse Laning
*/

#include "request_header.h"

using webserver::http::request::RequestHeader;

RequestHeader::RequestHeader() noexcept
    : Header({"Accept",
              "Accept-Charset",
              "Accept-Encoding",
              "Accept-Charset",
              "Accept-Language",
              "Authorization",
              "Except",
              "From",
              "Host",
              "If-Match",
              "If-Modified-Since",
              "If-None-Match",
              "If-Range",
              "If-Unmodified-Since",
              "Max-Forwards",
              "Proxy-Authorization",
              "Range",
              "Referer",
              "TE",
              "User-Agent"}) {}
