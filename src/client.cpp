#include "Inc.hpp"

Client::Client()
		: fd(-1),
			chunkSize(-1) {}

Client::Client(int fd, ServerConf &serverconf)
		: fd(fd),
			chunkSize(-1),
			srvconf(serverconf) {}

Client &Client::operator=(Client const &_2Copy)
{
	this->fd = _2Copy.fd;
	this->chunkSize = _2Copy.chunkSize;
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

void Client::addChunkedBody()
{
	std::string rawBody;

	while (rawBody.size())
	{
		rawBody = rawContent.substr(0, rawContent.find('\n'));
		rawContent.erase(rawContent.begin(), rawContent.begin() + rawBody.size());
		if (chunkSize == -1)
		{
			try
			{
				chunkSize = std::stoi(rawBody);
			}
			catch(const std::exception& e)
			{
				request.setValidity(false);
			}
		}
		else if (chunkSize < 0)
			request.setValidity(false);
		else if (chunkSize > 0)
		{
			rawBody = rawContent.substr(0, rawContent.find('\n'));
			rawContent.erase(rawContent.begin(), rawContent.begin() + rawBody.size());
			if ((int)rawBody.size() != chunkSize)
			{
				request.setValidity(false);
				return ;
			}
			forup(i, 0, rawContent.size())
				request.getBody().push_back(rawBody[i]);
		}
		else
			return ;
	}
}

void Client::addNormalBody()
{
	size_t i = 0;

	while (i < rawContent.size() && (int)request.getBody().size() < request.getBodyLength())
		request.getBody().push_back(rawContent[i++]);
	rawContent.erase(rawContent.begin(), rawContent.begin() + i);
}

void Client::addRawRequest(std::string buffer)
{
	this->rawContent += buffer;
	if (request.empty() && rawContent.find("\r\n\r\n") != std::string::npos)
	{
		splitRawRequest();
		request.addRawContent(rawContent);
		request.parse();
		this->rawContent.erase(this->rawContent.begin(), this->rawContent.begin() + this->rawContent.find("\r\n\r\n") + 4);
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
	if (request.isRequestChunked())
	{
		addChunkedBody();
		if (chunkSize == 0)
		{
			response.generateResponse(request, srvconf);
			return ;
		}
	}
	if (request.bodyDoesExist())
	{
		addNormalBody();
		if ((int)request.getBody().size() == request.getBodyLength())
		{
			response.generateResponse(request, srvconf);
			return ;
		}
	}
}

int Client::getFd() { return fd; }

Request Client::getRequest() { return request; }

std::string Client::getRawContent() { return this->rawContent; }

Response Client::getResponse() { return this->response; }

Client::~Client() {}