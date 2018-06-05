#pragma once

#include <string>
#ifdef _WIN32
#include <Windows.h>
#define RTLD_LAZY		0x00001
#define RTLD_NOW		0x00002
#define RTLD_NOLOAD		0x00004
#define RTLD_DEEPBIND	0x00008
#define RTLD_GLOBAL		0x00100
#define RTLD_LOCAL		0
#define RTLD_NODELETE	0x01000
#else
#include <dlfcn.h>
#endif

#if _COMPILE_WEBSERVER_DLL
#define LIBEXPORT __declspec(dllexport)
#else
#define LIBEXPORT __declspec(dllimport)
#endif

#pragma warning(disable : 4251)

namespace webserver
{
	namespace utils
	{
		class LIBEXPORT LibUtils
		{
		public:
#ifdef _WIN32
			constexpr static const char* libExt = ".dll";
			using LIBHANDLE = HINSTANCE;
			using LIBFCNPTR = FARPROC;
#else
			constexpr static const char* libExt = ".so";
			using LIBHANDLE = void*;
			using LIBFCNPTR = void*;
#endif
			static LIBHANDLE dlopen(const std::string& filename, int flags);
			static int dlclose(LIBHANDLE handle);
			static LIBFCNPTR dlsym(LIBHANDLE handle, const std::string& symbol);
			static std::string dlerror();
		private:
			LibUtils() {}
		};
	}
}