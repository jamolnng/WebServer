/*
Copyright 2018 Jesse Laning
*/

#include <cctype>
#include "string_utils.h"
#include "win_utils.h"

using webserver::utils::StringUtils;
using webserver::utils::WinUtils;

char my_toupper(char ch) {
  return static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
}

char my_tolower(char ch) {
  return static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
}

void StringUtils::upper(std::string& text) {
  std::transform(text.begin(), text.end(), text.begin(), my_toupper);
}

void StringUtils::lower(std::string& text) {
  std::transform(text.begin(), text.end(), text.begin(), my_tolower);
}

void StringUtils::triml(std::string& text) {
  if (!text.empty()) {
    std::string::iterator pos = text.begin();
    while (pos != text.end() && std::isspace(*pos)) pos++;

    text.erase(text.begin(), pos);
  }
}

void StringUtils::triml(std::string& text, const char* toremove) {
  if (!text.empty()) {
    std::string::size_type pos = text.find_first_not_of(toremove);
    if (std::string::npos != pos)
      text.erase(0, pos);
    else
      text.clear();
  }
}

void StringUtils::trimr(std::string& text) {
  if (!text.empty()) {
    std::string::iterator pos = text.end() - 1;
    while (pos != text.begin() && std::isspace(*pos)) pos--;

    text.erase(pos + 1, text.end());
  }
}

void StringUtils::trimr(std::string& text, const char* toremove) {
  if (!text.empty()) {
    std::string::size_type pos = text.find_last_not_of(toremove);
    if (std::string::npos != pos)
      text.erase(pos + 1);
    else
      text.clear();
  }
}

void StringUtils::trim(std::string& text) {
  triml(text);
  trimr(text);
}

void StringUtils::trim(std::string& text, const char* toremove) {
  triml(text, toremove);
  trimr(text, toremove);
}

std::vector<std::string> StringUtils::split(std::istringstream& ss, char delim,
                                            size_t max) {
  std::vector<std::string> all;
  std::string line;
  while (std::getline(ss, line, delim)) {
    trim(line);
    all.push_back(line);
  }
  if (max == 0) max = all.size();
  std::vector<std::string> elems;
  if (all.size() > max) {
    elems.insert(elems.end(), all.begin(), all.begin() + max - 1);
    std::string last;
    for (auto it = all.begin() + max - 1; it != all.end(); ++it)
      last += *it + std::string(1, delim);
    last = last.substr(0, last.size() - 1);
    trim(last);
    elems.push_back(last);
  } else {
    elems = all;
  }
  return elems;
}

std::vector<std::string> StringUtils::split(const std::string& s, char delim,
                                            size_t max) {
  std::istringstream iss(s);
  return split(iss, delim, max);
}

std::string StringUtils::strerror(int errnum) {
#ifdef _WIN32
  return WinUtils::GetLastErrorAsString();
#else
  return std::string(std::strerror(errnum));
#endif
}
