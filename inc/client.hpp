#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include "inc.hpp"

class Client
{
private:
	int fd;
	size_t chunkSize;
	Request request;
	Response response;
	ServerConf srvconf;
	std::string remaining;
	std::string rawContent;

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
	void addNormalBody();
	void addChunkedBody();
	void makeRequest();

	void nextRequest();
};

#endif