#ifndef __POLLGE_HPP__
#define __POLLGE_HPP__
#include "inc.hpp"

class pollge
{
private:
	int timeout, nfds;
	bool end_server, compress_array;
	char buffer[80];
	std::vector<struct pollfd> fds;
	std::map<int, int> sd2srv;
public:
	pollge();
	void _addSd(int sd, int srvIndex);
	void _runPoll();
	void _sdAccept(int sd);
	void _sdReceive(int i, bool &close_conn);
	~pollge();
};

#endif