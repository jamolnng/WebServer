#pragma once
#include <filesystem>
#ifdef _MSC_VER
namespace std
{
	namespace filesystem
	{
		using namespace std::experimental::filesystem;
	}
}
#endif