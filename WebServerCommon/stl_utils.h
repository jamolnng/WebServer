/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <algorithm>
#include <cctype>
#include <map>
#include <set>
#include <string>
#include "lib_utils.h"
namespace webserver {
namespace utils {
class LIBEXPORT STLUtils {
 public:
  struct ci_less {
    // case-independent (ci) compare_less binary function
    struct nocase_compare {
      bool operator()(const unsigned char& c1, const unsigned char& c2) const {
        return std::tolower(c1) < std::tolower(c2);
      }
    };
    bool operator()(const std::string& s1, const std::string& s2) const {
      return std::lexicographical_compare(s1.begin(), s1.end(),  // source range
                                          s2.begin(), s2.end(),  // dest range
                                          nocase_compare());     // comparison
    }
  };

  template <typename key, typename val>
  using ci_map = std::map<key, val, ci_less>;
  template <typename val>
  using ci_set = std::set<val, ci_less>;

  template <typename Container>
  static bool inContainer(const std::string val, const Container& cont) {
    return std::find(cont.begin(), cont.end(), val) != cont.end();
  }

 private:
  STLUtils() = delete;
};
}  // namespace utils
}  // namespace webserver
