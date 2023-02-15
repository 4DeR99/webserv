#include "inc.hpp"

Server::Server()
{
	this->sd = -1;
	this->end_server = this->compress_array = false;
	this->on = 1;
	this->nfds = 1;
}

void Server::socket_set()
{
	int rc;

	// CREATING A IPV6 SOCKET
	this->sd = socket(AF_INET6, SOCK_STREAM, 0);
	if (this->sd < 0)
	{
		perror("socket() failed");
		exit(-1);
	}
	// ALLOWING SD TO BE REUSABLE
	rc = setsockopt(this->sd, SOL_SOCKET, SO_REUSEADDR,
									(char *)&this->on, sizeof(this->on));
	if (rc < 0)
	{
		perror("setsockopt() failed");
		close(this->sd);
		exit(-1);
	}
	// SET SD TO BE NONBLOCKING
	// rc = ioctl(this->sd, FIONBIO, (char *)&this->on);
	rc = fcntl(this->sd, F_SETFL, O_NONBLOCK);
	if (rc < 0)
	{
		perror("ioctl() failed");
		close(this->sd);
		exit(-1);
	}
}

void Server::socket_bind()
{
	int rc;

	memset(&this->addr, 0, sizeof(this->addr));
	this->addr.sin6_family = AF_INET6;
	memcpy(&this->addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
	this->addr.sin6_port = htons(SERVER_PORT);
	rc = ::bind(this->sd,
							(struct sockaddr *)&this->addr, sizeof(this->addr));
	if (rc < 0)
	{
		perror("bind() failed");
		close(this->sd);
		exit(-1);
	}
}

void Server::socket_listen()
{
	int rc;

	rc = listen(this->sd, 32);
	if (rc < 0)
	{
		perror("listen() failed");
		close(this->sd);
		exit(-1);
	}
}

void Server::socket_poll()
{
	int current_size;
	bool close_conn;
	int rc;

	memset(this->fds, 0, sizeof(this->fds));
	this->fds[0].fd = this->sd;
	this->fds[0].events = POLLIN;
	this->timeout = 3 * 60 * 1000;
	while (this->end_server == false)
	{
		// CALL POLL() AND WAIT 3MIN FOR IT TO COMPLETE
		std::cout << "Waiting on poll()..." << std::endl;
		rc = poll(this->fds, this->nfds, this->timeout);
		// CHECK IF POOL() FAILED
		if (rc < 0)
		{
			perror("  poll() failed");
			break;
		}
		// CHECK IF THE 3MIN EXPIRED
		if (rc == 0)
		{
			std::cout << "  poll() timed out.  End program." << std::endl;
			break;
		}
		current_size = this->nfds;
		for (int i = 0; i < current_size; i++)
		{
			if (this->fds[i].revents == 0)
				continue;
			if (this->fds[i].fd == this->sd)
			{
				std::cout << " Listening socket is readable" << std::endl;
				this->socket_accept();
			}
			else
			{
				std::cout << " Descriptor" << this->fds[i].fd << "is readable" << std::endl;
				close_conn = false;
				this->socket_receive(i, close_conn);
				if (close_conn)
				{
					close(this->fds[i].fd);
					this->fds[i].fd = -1;
					compress_array = true;
				}
			}
		}
		if (compress_array)
		{
			compress_array = false;
			for (int i = 0; i < this->nfds; i++)
			{
				if (this->fds[i].fd == -1)
				{
					for (int j = i; j < this->nfds; j++)
						this->fds[j].fd = fds[j + 1].fd;
					i--;
					this->nfds--;
				}
			}
		}
	}
}

void Server::socket_receive(int i, bool &close_conn)
{
	int rc;
	int len;

	do
	{
		// RECEIVE DATA ON THIS CONNECTION UNTIL THE RECV FAILS WITH EWOULDBLOCK
		// IF ANY OTHER FAILURE OCCURS WE WILL CLOSE THE CONNECITON
		rc = recv(this->fds[i].fd, this->buffer, sizeof(this->buffer), 0);
		if (rc < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				perror("  recv() failed");
				close_conn = true;
			}
			break;
		}
		// CHECK TO SEE IF THE CONNECTION HAS BEEN CLOSED BY THE CLIENT
		if (rc == 0)
		{
			std::cout << "  Connection closed" << std::endl;
			close_conn = true;
			break;
		}
		len = rc;
		std::cout << len << " bytes received" << std::endl;
		// SEND DATA BACK TO THE CLIENT
		rc = send(this->fds[i].fd, this->buffer, len, 0);
		if (rc < 0)
		{
			perror("  send() failed");
			close_conn = true;
			break;
		}
	} while (true);
}

void Server::socket_accept()
{
	int new_sd = -1;

	do
	{
		new_sd = accept(this->sd, NULL, NULL);
		if (new_sd < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				perror("  accept() failed");
				end_server = true;
			}
			break;
		}
		std::cout << "  New incoming connection - " << new_sd << std::endl;
		this->fds[nfds].fd = new_sd;
		this->fds[nfds].events = POLLIN;
		this->nfds++;
	} while (new_sd != -1);
}

void Server::launch()
{
	std::cout << "Launching server..." << std::endl;
	this->socket_set();
	this->socket_bind();
	this->socket_listen();
	this->socket_poll();
}

Server::~Server()
{
	for (int i = 0; i < this->nfds; i++)
	{
		if (this->fds[i].fd >= 0)
			close(this->fds[i].fd);
	}
}