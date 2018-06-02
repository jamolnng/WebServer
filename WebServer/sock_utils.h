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
			static int init(void)
			{
#ifdef _WIN32
				WSADATA wsa_data;
				return WSAStartup(MAKEWORD(1, 1), &wsa_data);
#else
				return 0;
#endif
			}

			static int quit(void)
			{
#ifdef _WIN32
				return WSACleanup();
#else
				return 0;
#endif
			}

			static int shutdown(SOCKET sock)
			{
#ifdef _WIN32
				return ::shutdown(sock, SD_BOTH);
#else
				return ::shutdown(sock, SHUT_RDWR);
#endif
			}

			static int close(SOCKET sock)
			{
#ifdef _WIN32
				return closesocket(sock);
#else
				return ::close(sock);
#endif
			}
		};
	}
}