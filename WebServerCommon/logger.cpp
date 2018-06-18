/*
Copyright 2018 Jesse Laning
*/

#include "logger.h"

using webserver::utils::Logger;

webserver::utils::Logger::~Logger() {
  for (auto* s : streams) s->flush();
}

void Logger::addStream(std::ostream* ostr) { streams.insert(ostr); }

Logger& Logger::instance() {
  static Logger l;
  return l;
}
