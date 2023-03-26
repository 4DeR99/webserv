#include "Inc.hpp"

Pollge::Pollge()
		: timeout(3 * 60 * 1000),
			end_server(false),
			compress_array(false) {}

Pollge::Pollge(std::vector<ServerConf> servers)
		: timeout(3 * 60 * 1000),
			end_server(false),
			compress_array(false),
			servers(servers) {}

void Pollge::_addSd(int sd, int srvIndex)
{
	struct pollfd pollfd;
	sd2srv[sd] = srvIndex;
	memset(&pollfd, 0, sizeof(pollfd));
	pollfd.fd = sd;
	pollfd.events = POLLIN;
	this->fds.push_back(pollfd);
}

void Pollge::_run()
{
	int rc;
	size_t current_size;
	bool close_conn;
	std::cout << "begin" << std::endl;
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
		current_size = this->fds.size();
		forup(i, 0, current_size)
		{
			if (this->fds[i].revents == 0)
				continue;
			if (sd2srv[this->fds[i].fd] > 0)
				this->_sdAccept(this->fds[i].fd);
			else
			{
				close_conn = false;
				this->_sdReceive(this->fds.at(i), close_conn);
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
					this->fds.pop_back();
				}
			}
		}
	}
}

void Pollge::_sdAccept(int sd)
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
		std::cout << "	New client connected " << std::endl;
		Client newClient(new_sd, servers[sd2srv[sd] - 1]);
		memset(&pollfd, 0, sizeof(pollfd));
		pollfd.fd = new_sd;
		pollfd.events = POLLIN;
		this->fds.push_back(pollfd);
		this->clients[new_sd] = newClient;
	} while (new_sd != -1);
}

void Pollge::_sdReceive(struct pollfd &pollfd, bool &close_conn)
{
	int rc;
	Client &client = this->clients[pollfd.fd];
	std::string buff;

	if ((rc = recv(pollfd.fd, this->buffer, sizeof(this->buffer), 0)) > 0)
	{
		forup(i, 0, (size_t)rc)
		{
			buff.push_back(this->buffer[i]);
		}
		client.addRawRequest(buff);
	}
	else if (rc == 0)
	{
		client.makeRequest();
		std::cout << " Connection closed" << std::endl;
		close_conn = true;
	}
	else
	{
		if (errno != EWOULDBLOCK)
		{
			std::cerr << " recv() failed" << std::endl;
			close_conn = true;
		}
	}
}

Pollge::~Pollge()
{
	sd2srv.clear();
}