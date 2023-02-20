#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include "inc.hpp"

class Client
{
private:
	int fd;
	Request request;
	std::string remaining;
	std::string rawContent;
public:
	Client(int fd);
	// void	saveRemaining(char *rest, size_t len);
	//getters
	int _getFd();
	Request _getRequest();
	char *_getRemaining();
	size_t _getRemainingLen();
	void addRawRequest(std::string rawContent);
	// char* addToContent(char* buffer, size_t len);
	~Client();
};

#endif