/*
Copyright 2018 Jesse Laning
*/
#pragma once
#include <string>
#include "versioning.h"
#include "wsc_version.h"
DECL_VERSION(WS, 0, 0, 1)

static const std::string WS_VER_PRETTY = "WS/" + WS_VER_STR + " WSCommon/" + WSC_VER_STR;
