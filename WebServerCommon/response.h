#pragma once
#include <string>
#include "lib_utils.h"
#include "status_line.h"
#include "general_header.h"
#include "entity_header.h"
#include "response_header.h"
namespace webserver
{
	namespace http
	{
		namespace response
		{
			class LIBEXPORT Response
			{
			public:
				Response() = default;

				void clear();
				std::string build();

				StatusLine& getStatusLine();
				message::GeneralHeader& getGeneralHeader();
				ResponseHeader& getResponseHeader();
				entity::EntityHeader& getEntityHeader();

			private:
				StatusLine statusLine{};
				message::GeneralHeader generalHeader{};
				ResponseHeader responseHeader{};
				entity::EntityHeader entityHeader{};
			};
		}
	}
}