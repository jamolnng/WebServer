#pragma once
#include "config.h"
#include "plugin.h"
#include "request.h"
namespace webserver
{
	namespace site
	{
		class Site
		{
		public:
			Site(const std::filesystem::path& site);

			const std::string& getName() const;
			const int getPort() const;
			const std::filesystem::path& getRoot() const;
			const bool isDefault() const;

			const std::string getDefaultResponseMessage(http::request::Request& request);
			const std::string getDefaultErrorResponseMessage(int code, http::request::Request& request) noexcept;
			const std::string getResponseMessage(
				http::request::Request& request,
				const std::vector<plugin::Plugin*>& plugins);
			const std::string getErrorResponseMessage(
				int code,
				http::request::Request& request,
				const std::vector<plugin::Plugin*>& plugins);

		private:
			Config config;
			std::string name;
			int port;
			std::filesystem::path root;
			bool defaultSite;
		};
	}
}