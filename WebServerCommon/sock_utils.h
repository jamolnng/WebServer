/*
Copyright 2018 Jesse Laning
*/

#pragma once

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

#include "lib_utils.h"

namespace webserver {
namespace utils {
class LIBEXPORT SocketUtils {
 public:
  static int init(void);
  static int quit(void);
  static int shutdown(SOCKET sock);
  static int close(SOCKET sock);
  static int ioctl(SOCKET sock, long cmd, int* argp);

 private:
  SocketUtils() = delete;
};
}  // namespace utils
}  // namespace webserver
