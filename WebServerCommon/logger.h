/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include "lib_utils.h"

#ifdef ERROR
#undef ERROR
#endif

namespace webserver {
namespace utils {
class LIBEXPORT Logger {
 public:
  Logger(Logger const&) = delete;
  void operator=(Logger const&) = delete;

  enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

  void addStream(std::ostream* ostr) { streams.push_back(ostr); }

  template <typename T>
  void log(LogLevel level, const T& t) {
    auto now_c =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    for (auto* s : streams) {
      (*s) << std::put_time(std::localtime(&now_c), "%a, %e %b %Y %T") << " - ";
      auto oldw = s->width();
      (*s) << std::setw(8) << std::left << levelNames[level] << std::right
           << std::setw(oldw) << " - ";
      (*s) << t << std::endl << std::flush;
    }
  }

  template <typename T>
  void debug(const T& t) {
    log(DEBUG, t);
  }

  template <typename T>
  void info(const T& t) {
    log(INFO, t);
  }

  template <typename T>
  void warning(const T& t) {
    log(WARNING, t);
  }

  template <typename T>
  void error(const T& t) {
    log(ERROR, t);
  }

  template <typename T>
  void critical(const T& t) {
    log(CRITICAL, t);
  }

  static Logger& instance();

 private:
  Logger(){};

  std::vector<std::ostream*> streams;
  LogLevel level{DEBUG};
  const std::vector<std::string> levelNames{
      {"DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"}};
};
}  // namespace utils
}  // namespace webserver
