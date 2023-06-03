#include "Inc.hpp"

Request::Request()
		:	type(UNKNOWN),
			bodyLength(0),
			locationIndex(NO_LOCATION),
			valid(true),
			bodyExist(false),
			requestChunked(false) {}

Request::Request(ServerConf &serverConf)
		:	type(UNKNOWN),
			bodyLength(0),
			locationIndex(NO_LOCATION),
			valid(true),
			bodyExist(false),
			requestChunked(false),
			serverConf(serverConf) {}

Request::Request(Request const &_2Copy) { this->operator=(_2Copy); }

Request &Request::operator=(Request const &_2Copy)
{
	this->requestContent = _2Copy.requestContent;
	this->body = _2Copy.body;
	this->valid = _2Copy.valid;
	this->type = _2Copy.type;
	this->url = _2Copy.url;
	this->absoluteUrl = _2Copy.absoluteUrl;
	this->rawContent = _2Copy.rawContent;
	this->headers = _2Copy.headers;
	this->bodyExist = _2Copy.bodyExist;
	this->requestChunked = _2Copy.requestChunked;
	this->bodyLength = _2Copy.bodyLength;
	this->locationIndex = _2Copy.locationIndex;
	this->serverConf = _2Copy.serverConf;
	return *this;
}

std::vector<std::string> Request::_split(std::string s, char c)
{
	std::string buff;
	std::stringstream str_str(s);
	std::vector<std::string> arr;
	while (getline(str_str, buff, c))
		arr.push_back(buff);
	return arr;
}

std::vector<std::string> Request::_splitRawcontent(std::string s)
{
	std::vector<std::string> arr;
	size_t index;
	while ((index = s.find("\r\n")) != std::string::npos)
	{
		std::string buff = s.substr(0, index);
		arr.push_back(buff);
		s.erase(0, index + 2);
	}
	arr.push_back(s);
	return arr;
}

void Request::_sweep(std::string &string)
{
	while (isspace(string.back()))
		string.erase(string.end() - 1);
	while (isspace(string.front()))
		string.erase(string.begin());
}

void Request::_parseUrl(std::string &url)
{
	size_t pos = url.find('/');
	std::string holder;
	std::vector<Location> locations;

	if (valid)
	{
		if (url.front() != '/' || url.find("/../") != std::string::npos)
		{
			valid = false;
			return;
		}
		locations = serverConf.getLocations();
		while (pos != std::string::npos)
		{
			holder = url.substr(0, pos + 1);
			forup(i, 0, locations.size())
			{
				if (holder == locations[i].getPath().substr(0, holder.size()))
					locationIndex = i;
			}
			pos = url.find('/', pos + 1);
		}
	}
	if (locationIndex == NO_LOCATION)
		valid = false;
	else
	{
		this->url = url;
		this->absoluteUrl = locations[locationIndex].getRoot() + url;
	}
}

void Request::_parseMethod()
{
	std::vector<std::string> tab = _split(requestContent[0], ' ');
	if (tab.size() != 3)
	{
		valid = false;
		return;
	}
	forup(i, 0, tab[0].size())
	{
		if (islower(tab[0][i]))
			valid = false;
	}
	_parseUrl(tab[1]);
	if (valid && tab[0] == "GET")
		type = GET;
	else if (valid && tab[0] == "POST")
		type = POST;
	else if (valid && tab[0] == "DELETE")
		type = DELETE;
	else if (valid)
		type = UNKNOWN;
	if (valid && tab[2] != "HTTP/1.1")
		valid = false;
	_parseUrl(tab[1]);
}

void Request::parse()
{
	_parseMethod();
	if (valid) {
		for (size_t i = 1; i < requestContent.size() && valid; i++) {
			if (requestContent[i].find(':') == requestContent[i].size() - 1)
				valid = false;
			if (requestContent[i].find(':') != std::string::npos) {
				std::string key = std::string(requestContent[i].begin(), std::find(requestContent[i].begin(), requestContent[i].end(), ':'));
				_sweep(key);
				forup(i, 0, key.size()) key[i] = tolower(key[i]);
				std::string value = std::string(std::find(requestContent[i].begin(), requestContent[i].end(), ':') + 1, requestContent[i].end());
				_sweep(value);
				if (key == "content-length") {
					if (requestChunked)
						valid = false;
					bodyExist = true;
					try {
						bodyLength = std::stoi(value);
					}
					catch (std::exception &e) {
						valid = false;
					}
				}
				else if (key == "transfer-encoding" && value == "chunked") {
					std::cout << "chunked request" << std::endl;
					if (!headers["content-length"].empty())
						valid = false;
					bodyExist = true;
					requestChunked = true;
				}
				headers[key] = value;
			}
		}
	}
}

void Request::setValidity(bool validity) { this->valid = validity; }

void Request::setServerConf(ServerConf &serverConf) { this->serverConf = serverConf; }

std::string Request::getrawContent() { return this->rawContent; }

bool Request::isValid() { return this->valid; }

int Request::getType() { return this->type; }

int Request::getLocationIndex() { return this->locationIndex; }

int Request::getBodyLength() { return this->bodyLength; }

std::string Request::getUrl() { return this->url; }

std::string Request::getAbsoluteUrl() { return this->absoluteUrl; }

std::map<std::string, std::string> Request::getHeaders() { return this->headers; }

std::vector<char>& Request::getBody() { return this->body; }

std::vector<std::string>& Request::getRequestContent() { return this->requestContent; }

bool Request::bodyDoesExist() { return this->bodyExist; }

bool Request::isRequestChunked() { return this->requestChunked; }

bool Request::empty() { return (url.empty() && type == UNKNOWN); }

void Request::addRawContent(std::string rawContent)
{
	this->rawContent = rawContent;
	this->requestContent = _splitRawcontent(rawContent);
}

void Request::clear()
{
}

Request::~Request()
{
	url.clear();
	headers.clear();
	requestContent.clear();
}