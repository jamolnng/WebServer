#pragma once
#include <string>
#include "lib_utils.h"

namespace webserver
{
	namespace plugin
	{
		class LIBEXPORT Plugin
		{
		public:
			Plugin(std::string name);

			const std::string& getName() const;

		private:
			std::string name;
		};
	}
}