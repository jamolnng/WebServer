/*
Copyright 2018 Jesse Laning
*/

#include "general_header.h"

using webserver::http::message::GeneralHeader;

GeneralHeader::GeneralHeader() noexcept
    : Header({"Cache-Control", "Connection", "Date", "Pragma", "Trailer",
              "Transfer-Encoding", "Upgrade", "Via", "Warning"}) {}
