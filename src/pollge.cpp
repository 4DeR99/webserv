#include "inc.hpp"

Pollge::Pollge()
		: end_server(false),
			compress_array(false),
			timeout(3 * 60 * 1000)
{
}

// std::vector<char *> Pollge::_split(char *s, char c)
// {
// 	std::string buff;
// 	std::stringstream str_str(s);
// 	std::vector<char *> arr;
// 	while (getline(str_str, buff, c))
// 		arr.push_back(buff);
// 	return arr;
// }

void Pollge::_addSd(int sd, int srvIndex)
{
	struct pollfd pollfd;
	sd2srv[sd] = srvIndex;
	memset(&pollfd, 0, sizeof(pollfd));
	pollfd.fd = sd;
	pollfd.events = POLLIN;
	this->fds.push_back(pollfd);
}

void Pollge::_runPoll()
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
		current_size = this->fds.size();
		forup(i, 0, current_size)
		{
			if (this->fds[i].revents == 0)
				continue;
			if (sd2srv[this->fds[i].fd] > 0)
			{
				std::cout << "	Listening socket is readable" << std::endl;
				this->_sdAccept(this->fds[i].fd);
			}
			else
			{
				std::cout << "	Descriptor" << this->fds[i].fd << "is readable" << std::endl;
				close_conn = false;
				this->_sdReceive();
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
		std::cout << "	New incoming connection - " << new_sd << std::endl;
		Client newClient(new_sd);
		memset(&pollfd, 0, sizeof(pollfd));
		pollfd.fd = new_sd;
		pollfd.events = POLLIN;
		this->fds.push_back(pollfd);
		this->clients[new_sd] = newClient;
	} while (new_sd != -1);
}

void Pollge::_sdReceive(struct pollfd &pollfd, bool &close_conn)
{
	int rc, len;
	Client client = this->clients[pollfd.fd];
	std::string buff;

	if (rc = recv(pollfd.fd, this->buffer, sizeof(this->buffer) , 0) > 0)
	{
		forup(i, 0, rc){
			buff.push_back(this->buffer[i]);
		}
		client.addRawRequest(buff);
		while (client.requestCompleted())
		{
			client.splitRawRequest();
			client.makeRequest();
			client.move2next();
		}
	}
	else if (rc == 0)
	{
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