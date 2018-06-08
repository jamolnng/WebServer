#pragma once
#include "site.h"
#include "config.h"

namespace webserver
{
	namespace site
	{
		class SiteManager
		{
		public:
			SiteManager(const webserver::Config& config);
			~SiteManager();

			void load(const std::filesystem::path& path);
			Site& get(const std::string& name);
			Site& operator[](const std::string& name);
			std::vector<Site*> operator*();
			Site& getDefault();

		private:
			std::map<std::string, Site> sites;
			webserver::Config config;
			Site* defaultSite{ nullptr };
		};
	}
}