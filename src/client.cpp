#include "inc.hpp"

Client::Client()
		: fd(-1) {}

Client::Client(int fd, ServerConf &serverconf)
		: fd(fd),
			srvconf(serverconf) {}

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
	return (rawContent.find("\r\n\r\n") != std::string::npos && !request.bodyDoesExist() && !request.isRequestChunked());
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

void Client::nextRequest()
{
	rawContent = remaining;
	remaining.clear();
	request.clear();
}

void Client::makeRequest()
{
	this->request.addRawContent(this->rawContent);
	this->request.parse();
}

void Client::addNormalBody()
{
	size_t i = 0;

	while (i < rawContent.size() && i < request.getBodyLength())
		request.getBody().push_back(rawContent[i]);
	rawContent.erase(rawContent.begin(), rawContent.begin() + i);
}

void Client::addRawRequest(std::string &buffer)
{
	this->rawContent += buffer;
	if (request.empty() && rawContent.find("\r\n\r\n") != std::string::npos)
	{
		splitRawRequest();
		request.addRawContent(rawContent);
		request.parse();
		if (!request.isValid() || !request.bodyDoesExist())
		{
			response.generateResponse(request, srvconf);
			nextRequest();
		}
		else
		{
			rawContent = remaining;
			remaining.clear();
		}
	}
	else if (request.isRequestChunked())
	{
		addChunkedBody();
	}
	else if (request.bodyDoesExist())
	{
		addNormalBody();
	}
}

int Client::getFd() { return fd; }

Request Client::getRequest() { return request; }

std::string Client::getRawContent() { return this->rawContent; }

Client::~Client() {}