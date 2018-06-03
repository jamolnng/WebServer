#pragma once
#include <string>
#include "lib_utils.h"
#include "config.h"

namespace webserver
{
	namespace plugin
	{
		class LIBEXPORT Plugin
		{
		public:
			Plugin(const webserver::config::Config* config);

		private:
			const config::Config* config;
		};
	}
}