#include "inc.hpp"

Client::Client()
		: fd(-1)
{
}

Client::Client(int fd, ServerConf &serverconf)
		: fd(fd),
			srvconf(serverconf)
{
}

Client &Client::operator=(Client const &_2Copy)
{
	this->fd = _2Copy.fd;
	this->request = _2Copy.request;
	this->remaining = _2Copy.remaining;
	this->rawContent = _2Copy.rawContent;
	return *this;
}

bool Client::requestCompleted()
{
	return (this->rawContent.find("\r\n\r\n") == std::string::npos ? false : true);
}

void Client::splitRawRequest()
{
	std::string::iterator b, e;
	b = this->rawContent.begin() + this->rawContent.find("\r\n\r\n") + 4;
	e = this->rawContent.end();
	this->remaining = std::string(b, e);
	b = this->rawContent.begin();
	e = this->rawContent.begin() + this->rawContent.find("\r\n\r\n");
	this->rawContent = std::string(b, e);
}

void Client::move2next()
{
	rawContent = remaining;
	remaining.clear();
	//! request.clear();
}

void Client::makeRequest()
{

	this->request.addRawContent(this->rawContent);
	this->request.parse();
}

void Client::addRawRequest(std::string &buffer)
{
	this->rawContent += buffer;
}

int Client::_getFd()
{
	return fd;
}

Request Client::_getRequest()
{
	return request;
}

std::string Client::getRawContent()
{
	return this->rawContent;
}

Client::~Client()
{
}