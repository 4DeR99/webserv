#include "inc.hpp"

Client::Client(int fd)
: fd(fd)
{
}

// char*		Request::addToContent(char* buffer, size_t len)
// {
// 	char *tmp;

// 	if (len == 0)
// 		return NULL;
// 	tmp = new char[this->contentLen + len + 1];
// 	strcpy(tmp, this->content);
// 	strcat(tmp, buffer);
// 	delete this->content;
// 	this->contentLen += len;
// 	this->content = tmp;
// }

// void Client::saveRemaining(char *rest, size_t len)
// {
// }

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

// char *Client::_getRemaining()
// {
// 	return remaining;
// }

// size_t Client::_getRemainingLen()
// {
// 	return remainingLen;
// }

Client::~Client()
{
}