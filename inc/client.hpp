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
	Client();
	Client(int fd);
	Client& operator=(Client const &_2Copy);
	~Client();

	void splitRawRequest();
	bool requestCompleted();

	int _getFd();
	Request _getRequest();

	void addRawRequest(std::string rawContent);
	void makeRequest();
	void makeResponse();

	void move2next();
};

#endif