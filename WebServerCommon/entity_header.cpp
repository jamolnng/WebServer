/*
Copyright 2018 Jesse Laning
*/

#include <sstream>
#include "entity_header.h"

using webserver::http::entity::EntityHeader;

EntityHeader::EntityHeader() noexcept
    : Header({"Allow", "Content-Encoding", "Content-Language", "Content-Length",
              "Content-Location", "Content-MD5", "Content-Range",
              "Content-Type", "Expires", "Last-Modified"}) {}

void EntityHeader::parse(std::map<std::string, std::string>& parts) {
  items.insert(parts.begin(), parts.end());
}

std::string EntityHeader::build() const {
  std::ostringstream oss;
  for (auto& p : items) oss << p.first << ": " << p.second << std::endl;
  return oss.str();
}
