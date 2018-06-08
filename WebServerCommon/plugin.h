#pragma once
#include <string>
#include "lib_utils.h"
#include "request.h"
#include "response.h"

namespace webserver
{
	namespace plugin
	{
		class LIBEXPORT Plugin
		{
		public:
			Plugin() = default;

			bool modifyRequestHeader(http::request::Request& request);
			bool getResponseMessage(std::string& body, const http::request::Request& request);
			bool getErrorResponseMessage(int code, std::string& body, const http::request::Request& request);
			bool getReponseHeader(http::response::Response& response);
		};
	}
}