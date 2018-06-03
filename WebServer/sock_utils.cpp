#include "sock_utils.h"

using namespace webserver::utils;

int SocketUtils::init(void)
{
#ifdef _WIN32
	WSADATA wsaData;
	return WSAStartup(MAKEWORD(1, 1), &wsaData);
#else
	return 0;
#endif
}

int SocketUtils::quit(void)
{
#ifdef _WIN32
	return WSACleanup();
#else
	return 0;
#endif
}

int SocketUtils::shutdown(SOCKET sock)
{
#ifdef _WIN32
	return ::shutdown(sock, SD_BOTH);
#else
	return ::shutdown(sock, SHUT_RDWR);
#endif
}

int SocketUtils::close(SOCKET sock)
{
#ifdef _WIN32
	return closesocket(sock);
#else
	return ::close(sock);
#endif
}

int SocketUtils::ioctl(SOCKET sock, long cmd, int* argp)
{
#ifdef _WIN32
	unsigned long ul;
	int ret = ioctlsocket(sock, cmd, &ul);
	*argp = (int)ul;
	return ret;
#else
	return ::ioctl(sock, cmd, argp);
#endif
}