#ifndef __POLLGE_HPP__
#define __POLLGE_HPP__
#include "Inc.hpp"

class Pollge
{
private:
	int timeout;
	bool end_server;
	bool compress_array;
	char buffer[1000];
	std::vector<struct pollfd> fds;
	std::map<int, int> sd2srv;
	std::map<int, Client> clients;
	std::vector<ServerConf> servers;
	std::vector<char*> _split(char *s, char c);
public:
	Pollge();
	Pollge(std::vector<ServerConf> &servers);
	~Pollge();

	void _addSd(int sd, int srvIndex, int sendBufferSize);
	void _run();
	void _sdAccept(int sd);
	void _sdReceive(int sd, bool &close_conn);
	void _sdSend(int sd, bool &close_conn);
};

#endif