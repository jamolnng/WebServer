#include "logger.h"

using webserver::utils::Logger;

Logger & Logger::instance()
{
  static Logger l;
  return l;
}
