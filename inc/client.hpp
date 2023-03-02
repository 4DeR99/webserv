#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include "inc.hpp"

class Client
{
private:
	int fd;
	Request request;
	ServerConf srvconf;
	std::string remaining;
	std::string rawContent;
	std::string lowerCaseRawContent;

public:
	Client();
	Client(int fd, ServerConf &serverconf);
	Client& operator=(Client const &_2Copy);
	~Client();

	void splitRawRequest();
	bool requestCompleted();

	int getFd();
	Request getRequest();
	std::string getRawContent();

	void addRawRequest(std::string &buffer);
	void makeRequest();

	void move2next();
};

#endif