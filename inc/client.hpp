#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include "Inc.hpp"

class Client
{
private:
	int fd;
	int chunkSize;
	long long sentBytes;
	Request request;
	Response response;
	ServerConf srvconf;
	std::string remaining;
	std::string rawContent;

public:
	Client();
	Client(int fd, ServerConf &serverconf);
	Client &operator=(Client const &_2Copy);
	~Client();

	void splitRawRequest();
	bool requestCompleted();

	// Getters
	int getFd();
	long long getSentBytes();
	Request &getRequest();
	std::string &getRawContent();
	Response &getResponse();
	ServerConf &getSrvConf();

	// Setters
	void addRawRequest(char *buffer, size_t size);
	void addNormalBody();
	void addChunkedBody();
	void addBodyboundary();
	void setSentBytes(long long sentBytes);

	// Request related methods
	void makeRequest();
	void nextRequest();
};

#endif