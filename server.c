#include <bits/getopt_core.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "server.h"

void init_windows_socket()
{
#if defined(_WIN32)
	WSADATA d;
	if (WSAStartup(MAKEWORD(2, 2), &d))
	{
		fprintf(stderr, "Failed to initialize windows socket\n");
		exit(EXIT_FAILURE);
	}

	WSACleanup();
#endif
}

void init_server(int port)
{
	init_windows_socket();
	printf("Configuring at local address\n");

	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	struct addrinfo *bind_address;
	int i = getaddrinfo(0, "8080", &hints, &bind_address);

	if (i != 0)
	{
		fprintf(stderr, "Failed to initialize server\n");
		exit(EXIT_FAILURE);
	}

	printf("Creating socket...\n");

	SOCKET socket_listen;
	socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);

	if (!ISVALIDSOCKET(socket_listen))
	{
		fprintf(stderr, "socket() failed! (%d)\n", GETSOCKERRNO());
		exit(EXIT_FAILURE);
	}

	int opts = 0;
	if (setsockopt(socket_listen, IPPROTO_IPV6, IPV6_V6ONLY, (void *)&opts, sizeof(opts)))
	{
	}

	printf("Binding socket at local address\n");

	if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen))
	{
		fprintf(stderr, "bind() failed! (%d)\n", GETSOCKERRNO());
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(bind_address);

	printf("Listening...\n");
	if (listen(socket_listen, 10) < 0)
	{
		fprintf(stderr, "listen() failed! (%d)\n", GETSOCKERRNO());
		exit(EXIT_FAILURE);
	}

	time_t timer;
	time(&timer);

	printf("Started at: %s", ctime(&timer));

	printf("Waiting for connection...\n");

	struct sockaddr_storage client_addr;
	socklen_t client_len = sizeof(client_addr);
	SOCKET sock_client = accept(socket_listen, (struct sockaddr *)&client_addr, &client_len);

	if (!ISVALIDSOCKET(sock_client))
	{
		fprintf(stderr, "accept() failed! (%d)\n", GETSOCKERRNO());
		exit(EXIT_FAILURE);
	}

	printf("Client connected!\n");

	char addr_buff[100];
	getnameinfo((struct sockaddr *)&client_addr, client_len, addr_buff, sizeof(addr_buff), 0, 0, NI_NUMERICHOST);
	printf("%s\n", addr_buff);

	printf("Reading request...\n");
	char req[1024];
	int bytes_recv = recv(sock_client, req, 1024, 0);
	printf("bytes %d bytes\n", bytes_recv);
	printf("%.*s\n", bytes_recv, req);

	printf("Sending response...\n");
	const char *response = "HTTP/1.1 200 OK\r\n"
						   "Connection: close\r\n"
						   "Content-Type: text/plain\r\n\r\n"
						   "Local time is: ";
	int bytes_sent = send(sock_client, response, strlen(response), 0);
	printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(response));

	time(&timer);
	char *time_msg = ctime(&timer);

	bytes_sent = send(sock_client, time_msg, strlen(time_msg), 0);
	printf("Sent %d of %d bytes\n", bytes_sent, (int)strlen(time_msg));
	printf("Closing connection...\n");

	CLOSESOCKET(sock_client);
	CLOSESOCKET(socket_listen);

#if defined(_WIN32)
	WSACleanup();
#endif
}
