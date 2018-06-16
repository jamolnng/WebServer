/*
Copyright 2018 Jesse Laning
*/

#include "http_utils.h"

#include <iostream>
#include <vector>
#include "string_utils.h"

using webserver::utils::HTTPUtils;
using webserver::utils::StringUtils;

std::map<std::string, std::string> HTTPUtils::parseURLEncoded(
    const std::string& encoded) {
  std::vector<std::string> vars = StringUtils::split(encoded, '&');
  std::vector<std::string> split;
  std::map<std::string, std::string> decoded;
  std::string item;
  std::string val;
  for (std::string& var : vars) {
    split = StringUtils::split(var, '=', 2);
    item = split[0];
    if (split.size() == 2)
      val = split[1];
    else
      val = "";
    decoded[urlDecode(item)] = urlDecode(val);
  }
  return decoded;
}

std::string HTTPUtils::urlDecode(const std::string& inurl) {
  std::string url = inurl;
  std::replace(url.begin(), url.end(), '+', ' ');
  std::string ret;
  char ch;
  int i, j;
  for (i = 0; i<url.length(); i++) {
    if (int(url[i]) == 37) {
      sscanf(url.substr(i + 1, 2).c_str(), "%x", &j);
      ch = static_cast<char>(j);
      ret += ch;
      i = i + 2;
    }
    else {
      ret += url[i];
    }
  }
  return (ret);
}