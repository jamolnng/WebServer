#pragma once
#include <string>

namespace webserver
{
	namespace plugin
	{
		class Plugin
		{
		public:
			Plugin(std::string name) : name(name) {}

			std::string getName() { return name; }

		private:
			std::string name;
		};
	}
}