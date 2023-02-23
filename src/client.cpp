#include "inc.hpp"

Client::Client()
: fd(-1)
{
}

Client::Client(int fd)
: fd(fd)
{
}

Client& Client::operator=(Client const &_2Copy)
{
	this->fd = _2Copy.fd;
	this->request = _2Copy.request;
	this->remaining = _2Copy.remaining;
	this->rawContent = _2Copy.rawContent;
	return *this;
}

bool Client::requestCompleted()
{
	return this->rawContent.find("/r/n/r/n") == std::string::npos ? false : true;
}

void Client::splitRawRequest()
{
	std::string::iterator b, e;
	b = this->rawContent.begin() + this->rawContent.find("\r\n\r\n") + 4;
	e = this->rawContent.end();
	this->remaining = std::string(b, e);
	b = this->rawContent.begin();
	e = this->rawContent.begin() + this->rawContent.find("\r\n\r\n") - 1;
	this->rawContent = std::string(b, e);
}

void Client::move2next()
{
	rawContent = remaining;
	remaining.clear();
	//! request.clear();
}

void Client::makeResponse()
{
	//! this->response.run(this->request);
}

void Client::makeRequest()
{
	this->request.getRawContent(this->rawContent);
	this->request.parse();
	this->makeResponse();
}

void Client::addRawRequest(std::string rawContent)
{
	this->rawContent += rawContent;
}

int Client::_getFd()
{
	return fd;
}

Request Client::_getRequest()
{
	return request;
}

Client::~Client()
{
}