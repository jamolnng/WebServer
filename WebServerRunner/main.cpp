#include <iostream>
#include <filesystem>

typedef int(__stdcall *webserverMain)(int, char*[]);

#ifdef _MSC_VER
namespace std { namespace filesystem
{
	using namespace std::experimental::filesystem;
}}
#endif
#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

int main(int argc, char* argv[])
{
	webserverMain main;
	std::filesystem::path p(argv[0]);
#ifdef _WIN32
	p = p.parent_path() / "WebServer.dll";
	HINSTANCE lib = LoadLibrary(p.generic_string().c_str());
	if (!lib)
	{
		std::cout << "Failed to load DLL" << std::endl;
		return -1;
	}
	main = (webserverMain)GetProcAddress(lib, "webserverMain");
#else
	p = p.parent_path() / "WebServer.so";
	void *lib = ::dlopen(p.generic_string().c_str());
	if (!lib)
	{
		std::cout << "Failed to load library" << std::endl;
		return -1;
	}
	main = (webserverMain)::dlsym(lib, "webserverMain");
#endif
	if (!main)
	{
		std::cout << "Failed to find hook" << std::endl;
#ifdef _WIN32
		FreeLibrary(lib);
#else
		::dlclose(lib);
#endif
		return -1;
	}
	int ret = main(argc, argv);
#ifdef _WIN32
	FreeLibrary(lib);
#else
	::dlclose(lib);
#endif
	return ret;
}