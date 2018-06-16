/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <string>
#include "entity_header.h"
#include "general_header.h"
#include "lib_utils.h"
#include "response_header.h"
#include "status_line.h"
namespace webserver {
namespace http {
namespace response {
class LIBEXPORT Response {
 public:
  Response() = default;

  void clear();
  std::string build() const;

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
}  // namespace response
}  // namespace http
}  // namespace webserver
