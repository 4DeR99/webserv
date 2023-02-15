#include "inc.hpp"

pollge::pollge()
		: end_server(false), compress_array(false), timeout(3 * 60 * 1000), nfds()
{
}

void pollge::_addSd(int sd, int srvIndex)
{
	struct pollfd pollfd;
	sd2srv[sd] = srvIndex;
	memset(&pollfd, 0, sizeof(pollfd));
	pollfd.fd = sd;
	pollfd.events = POLLIN;
	this->fds.push_back(pollfd);
	this->nfds++;
}

void pollge::_runPoll()
{
	int rc, current_size;
	bool close_conn;
	while (this->end_server == false)
	{
		// CALL POLL() AND WAIT FOR INC CONNECTIONS
		rc = poll(this->fds.data(), this->fds.size(), this->timeout);
		// CHECK IF POLL() FAILED
		if (rc < 0)
			throw std::runtime_error("poll() failed");
		// CHECK IF THE 3MIN EXPIRED
		if (rc == 0)
		{
			std::cout << "	poll() timed out. End program." << std::endl;
			break;
		}
		current_size = this->nfds;
		forup(i, 0, current_size)
		{
			if (this->fds[i].revents == 0)
				continue;
			if (sd2srv[this->fds[i].fd] > 0)
			{
				std::cout << "	Listening socket is readable" << std::endl;
				// this->sdAccept();
			}
			else
			{
				std::cout << "	Descriptor" << this->fds[i].fd << "is readable" << std::endl;
				close_conn = false;
				// this->sdReceive();
				if (close_conn)
				{
					close(this->fds[i].fd);
					this->fds[i].fd = -1;
					this->compress_array = true;
				}
			}
		}
		if (this->compress_array)
		{
			compress_array = false;
			forup(i, 0, this->fds.size())
			{
				if (this->fds[i].fd == -1)
				{
					forup(j, i, this->fds.size())
					{
						this->fds[j].fd = fds[j + 1].fd;
					}
					i--;
					this->nfds--;
					this->fds.pop_back();
				}
			}
		}
	}
}

void pollge::_sdAccept(int sd)
{
	int new_sd = -1;
	struct pollfd pollfd;

	do
	{
		new_sd = accept(sd, NULL, NULL);
		if (new_sd < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				std::cerr << "  accept() failed" << std::endl;
				end_server = true;
			}
			break;
		}
		std::cout << "	New incoming connection - " << new_sd << std::endl;
		memset(&pollfd, 0, sizeof(pollfd));
		pollfd.fd = new_sd;
		pollfd.events = POLLIN;
		this->fds.push_back(pollfd);
		this->nfds++;
	} while (new_sd != -1);
}

void pollge::_sdReceive(int i, bool &close_conn)
{
	int rc, len;

	while (true)
	{
		// RECEIVE DATA ON THIS CONNECTION UNTIL THE RECV FAILS WITH EWOULDBLOCK
		// IF ANY OTHER FAILURE OCCURS WE WILL CLOSE THE CONNECITON
		rc = recv(this->fds[i].fd, this->buffer, sizeof(this->buffer), 0);
		if (rc < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				std::cerr << "  recv() failed" << std::endl;
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
		// SEND RESPONSE BACK TO THE CLIENT
		// rc = send(this->fds[i].fd, this->buffer, len, 0);
		if (rc < 0)
		{
			perror("  send() failed");
			close_conn = true;
			break;
		}
	}
}

pollge::~pollge()
{
	sd2srv.clear();
}