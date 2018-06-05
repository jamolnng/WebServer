#include "lib_utils.h"
#include "win_utils.h"
#include "string_utils.h"

using namespace webserver::utils;

LibUtils::LIBHANDLE LibUtils::dlopen(const std::string& filename, int flags)
{
#ifdef _WIN32
	return LoadLibrary(filename.c_str());
#else
	return ::dlopen(filename.c_str(), flags)
#endif
}

int LibUtils::dlclose(LIBHANDLE handle)
{
#ifdef _WIN32
	return FreeLibrary(handle);
#else
	return ::dlclose(handle);
#endif
}

LibUtils::LIBFCNPTR LibUtils::dlsym(LIBHANDLE handle, const std::string& symbol)
{
#ifdef _WIN32
	return GetProcAddress(handle, symbol.c_str());
#else
	return ::dlsym(handle, symbol.c_str());
#endif
}

std::string LibUtils::dlerror()
{
#ifdef _WIN32
	return WinUtils::GetLastErrorAsString();
#else
	return std::string(::dlerror());
#endif
}