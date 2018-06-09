/*
Copyright 2018 Jesse Laning
*/

#include "status_line.h"

using webserver::http::response::StatusLine;

StatusLine::StatusLine() noexcept
    : Line({"HTTP-Version", "Status-Code", "Reason-Phrase"}) {}
