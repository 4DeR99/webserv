#include "Inc.hpp"

Pollge::Pollge()
		: timeout(3 * 60 * 1000),
			end_server(false),
			compress_array(false) {}

Pollge::Pollge(std::vector<ServerConf> &servers)
		: timeout(3 * 60 * 1000),
			end_server(false),
			compress_array(false),
			servers(servers) {}

void Pollge::_addSd(int sd, int srvIndex, int sendBufferSize)
{
	struct pollfd pollfd;
	sd2srv[sd] = srvIndex;
	servers[srvIndex - 1].setSendBufferSize(sendBufferSize);
	servers[srvIndex - 1].setSd(sd);
	memset(&pollfd, 0, sizeof(pollfd));
	pollfd.fd = sd;
	pollfd.events = POLLIN | POLLOUT;
	pollfd.revents = 0;
	this->fds.push_back(pollfd);
}

void Pollge::_run()
{
	int rc;
	bool close_conn;
	std::cout << "Begin" << std::endl;
	while (true)
	{
		// CALL POLL() AND WAIT FOR INC CONNECTIONS
		rc = poll(this->fds.data(), this->fds.size(), this->timeout);
		// CHECK IF POLL() FAILED
		if (rc < 0)
			throw std::runtime_error("poll() failed: " + std::string(strerror(errno)));
		// CHECK IF THE 3MIN EXPIRED
		if (rc == 0)
		{
			std::cout << "	poll() timed out. End program." << std::endl;
			break;
		}
		forup(i, 0, this->fds.size())
		{
			if (this->fds[i].revents == 0)
				continue;
			if (this->fds[i].revents & POLLIN)
			{
				if (sd2srv[this->fds[i].fd] > 0)
					this->_sdAccept(this->fds[i].fd);
				else
				{
					close_conn = false;
					this->_sdReceive(this->fds[i].fd, close_conn);
					if (close_conn)
					{
						close(this->fds[i].fd);
						this->fds[i].fd = -1;
						this->compress_array = true;
					}
				}
			}
			if (this->fds[i].revents & POLLOUT)
			{
				close_conn = false;
				this->_sdSend(this->fds[i].fd, close_conn);
				if (close_conn)
				{
					close(this->fds[i].fd);
					this->fds[i].fd = -1;
					this->compress_array = true;
					this->clients.erase(this->fds[i].fd);
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
					forup(j, i, this->fds.size()-1)
						this->fds[j].fd = fds[j + 1].fd;
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

	new_sd = accept(sd, NULL, NULL);
	if (new_sd < 0)
		throw std::runtime_error("accept() failed: " + std::string(strerror(errno)));
	// Set the socket to be nonblocking
	if (fcntl(new_sd, F_SETFL, O_NONBLOCK) < 0)
		throw std::runtime_error("fcntl() failed");
	std::cout << "	New client connected " << std::endl;
	Client newClient(new_sd, servers[sd2srv[sd] - 1]);
	memset(&pollfd, 0, sizeof(pollfd));
	pollfd.fd = new_sd;
	pollfd.events = POLLIN | POLLOUT;
	pollfd.revents = 0;
	this->fds.push_back(pollfd);
	this->clients[new_sd] = newClient;
}

void Pollge::_sdReceive(int sd, bool &close_conn)
{
	long long rc;
	Client &client = this->clients[sd];
	std::string buff;

	if ((rc = recv(sd, this->buffer, sizeof(this->buffer), 0)) > 0)
		client.addRawRequest(this->buffer, rc);
	else if (rc == 0)
	{
		std::cout << " Connection closed" << std::endl;
		close_conn = true;
	}
	else if (rc == -1)
	{
		std::cerr << " recv() failed" << std::endl;
		close_conn = true;
	}
}

void Pollge::_sdSend(int sd, bool &close_conn)
{
	Client &client = this->clients[sd];
	long long rc = client.getSentBytes();
	if (client.getResponse().isResponseCompleted())
	{
		size_t size = client.getResponse().getGeneratedResponse().size();
		if (size)
		{
			long long tmp = 0;
			size_t to_send = SEND_BUFFER_SIZE;
			if (size - rc < to_send)
				to_send = size - rc;
			tmp = send(sd, client.getResponse().getGeneratedResponse().c_str() + rc, to_send, 0);
			if (tmp < 0)
			{
				std::cerr << "send() failed" << std::endl;
				client.getResponse().clear();
				client.setSentBytes(0);
				close_conn = true;
				return ;
			}
			rc += tmp;
			client.setSentBytes(rc);
			if (rc == (long long)size)
			{
				client.getResponse().clear();
				client.setSentBytes(0);
				close_conn = true;
			}
		}
	}
}

Pollge::~Pollge()
{
	sd2srv.clear();
}