#ifndef __POLLGE_HPP__
#define __POLLGE_HPP__
#include "inc.hpp"

class Pollge
{
private:
	int timeout;
	bool end_server, compress_array;
	char buffer[80];
	std::vector<struct pollfd> fds;
	std::map<int, int> sd2srv;
	std::map<int, Client> clients;
	std::vector<char*> _split(char *s, char c);
public:
	Pollge();
	~Pollge();
	 
	void _addSd(int sd, int srvIndex);
	void _runPoll();
	void _sdAccept(int sd);
	void _sdReceive(struct pollfd& pollfd, bool &close_conn);
};

#endif