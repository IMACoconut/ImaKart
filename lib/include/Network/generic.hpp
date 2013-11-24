#pragma once


#if defined(_WIN32)
	#define USE_WINDOWS
	#include <winsock2.h>
	#include <ws2tcpip.h>

	#if defined(_MSC_VER)
    	#pragma comment(lib, "ws2_32")
	#endif

#elif defined(__linux__)
	#define USE_LINUX
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <netinet/in.h>
	#include <sys/ioctl.h>
	#include <sys/socket.h>
	#include <unistd.h>

	typedef sockaddr SOCKADDR;
	typedef sockaddr_in SOCKADDR_IN;
	typedef sockaddr_in6 SOCKADDR_IN6;
	typedef in_addr IN_ADDR;
	typedef in6_addr IN6_ADDR;
	typedef int SOCKET;
	#define INVALID_SOCKET (SOCKET)(~0)
	#define SOCKET_ERROR -1
	
#else
	#define USE_NONE
#endif

extern void pause(uint32_t msec);