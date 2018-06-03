#pragma once

#include <string>

#if _COMPILE_WEBSERVER_DLL
#define LIBEXPORT __declspec(dllexport)
#else
#define LIBEXPORT __declspec(dllimport)
#endif

#pragma warning(disable : 4251)