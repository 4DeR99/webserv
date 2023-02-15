#ifndef __SERVER_HPP__
#define __SERVER_HPP__
#include "inc.hpp"
#define SERVER_PORT 12345

class Server
{
private:
	int sd, on, nfds, timeout;
	bool end_server, compress_array;
	char buffer[80];
	struct sockaddr_in6 addr;
	struct pollfd fds[200];

public:
	Server();
	void launch();
	void socket_set();
	void socket_bind();
	void socket_listen();
	void socket_poll();
	void socket_accept();
	void socket_receive(int i, bool &close_conn);
	~Server();
};

#endif