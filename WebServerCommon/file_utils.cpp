/*
Copyright 2018 Jesse Laning
*/

#include "file_utils.h"

using webserver::utils::FileUtils;

std::filesystem::path FileUtils::getParent(const std::filesystem::path& p1,
                                           const std::filesystem::path& p2) {
  std::error_code ec;
  for (auto p = p1; !p.empty() && !std::filesystem::equivalent(p, "\\", ec) &&
                    ec.value() == 0;
       p = p.parent_path()) {
    for (auto o = p2; !o.empty() && !std::filesystem::equivalent(o, "\\", ec) &&
                      ec.value() == 0;
         o = o.parent_path()) {
      if (o == p) return o;
    }
  }
  return "";
}
