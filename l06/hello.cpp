#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cerrno>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // inet_ntoa

void err(const char *msg) { perror(msg); exit(EXIT_FAILURE); }

int main(int argc, char* argv[])
{
	int serverSock;

	if (argc < 2) {
		fprintf(stderr, "USAGE:\n");
		fprintf(stderr, "  hello PORT_NUMBER\n");
		exit(EXIT_FAILURE);
	}

	serverSock = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSock == -1)
		err("socket");

	uint16_t portno = atoi(argv[1]);  // TODO strtol to detect errors

	struct sockaddr_in addr; // ipv4 address and port
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY; // listen on any address / interface
	addr.sin_port = htons(portno); // convert port number to network byte order

	if (bind(serverSock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		err("bind");

	if (listen(serverSock, 10) == -1)
		err("listen");

	while (1) {
		struct sockaddr_in clientAddr;
		socklen_t clientAddrSize = sizeof(clientAddr);
		// wait for new connections
		int clientSock = accept(serverSock, (struct sockaddr *) &clientAddr,
				&clientAddrSize);
		if (clientSock == -1 && (errno != EAGAIN || errno != EINTR))
			err("accept");

		if (clientSock != -1) {
			// we have a new connection
			fprintf(stderr, "New connection from %s:%d\n",
					inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

			// TODO handle connection
		}
	}
}

/* vim: set sw=4 sts=4 ts=4 noet : */
