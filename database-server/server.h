#pragma once

#if defined(_WIN32) // Windows stuff

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x600
#endif // _WIN32_WINNT
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define CLOSESOCKET(s) closesocket(s)
#define GETSOCKERRNO() (WSAGetLastError())

#else // POSIX/BSD stuff

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define ISVALIDSOCKET(s) ((s) >= 0)
#define SOCKET int
#define CLOSESOCKET(s) close(s)
#define GETSOCKERRNO() (errno)

#endif

#include "common.h"

// Mostly for windows
void init_windows_socket();
void init_server(int port);
