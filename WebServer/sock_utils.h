#pragma once

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <ws2tcpip.h>
#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#endif

namespace webserver
{
	namespace utils
	{
		class SocketUtils
		{
		public:
			static int init(void);
			static int quit(void);
			static int shutdown(SOCKET sock);
			static int close(SOCKET sock);
			static int ioctl(SOCKET sock, long cmd, int* argp);
		};
	}
}