#include "inc.hpp"

Request::Request()
	:	valid(true),
		type(UNKNOWN),
		locationIndex(NO_LOCATION)
{
}

Request::Request(ServerConf &serverConf)
	:	valid(true),
		type(UNKNOWN),
		serverConf(serverConf),
		locationIndex(NO_LOCATION)
{
}

Request::Request(Request const &_2Copy)
{
	this->operator=(_2Copy);
}

Request& Request::operator=(Request const &_2Copy)
{
	this->requestContent = _2Copy.requestContent;
	this->body = _2Copy.body;
	this->valid = _2Copy.valid;
	this->type = _2Copy.type;
	this->url = _2Copy.url;
	this->rawContent = _2Copy.rawContent;
	this->headers = _2Copy.headers;
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
		s.erase(0, index+2);
	}
	arr.push_back(s);
	return arr;
}

void Request::_parseUrl(std::string &url)
{
	size_t pos = 0;
	std::string holder;
	std::vector<Location> locations;

	if (valid)
	{
		if (url.front() != '/' || url.find("/../") != std::string::npos)
			valid = false;
		locations = serverConf.getLocations();
		while (pos != std::string::npos)
		{
			holder = url.substr(0, pos+1);
			forup(i, 0, locations.size())
			{
				if (holder == locations[i].getPath().substr(0, holder.size()))
					locationIndex = i;
			}
			pos = url.find('/', pos + 1);
		}
	}
}

void Request::_parseMethod()
{
	std::vector<std::string> tab = _split(requestContent[0], ' ');
	if (tab.size() != 3)
	{
		valid = false;
		return ;
	}
	forup(i, 0, tab[0].size())
	{
		if (islower(tab[0][i]))
			valid = false;
	}
	if (valid && tab[0] == "GET")
		type = GET;
	else if (valid && tab[0] == "POST")
		type = POST;
	else if (valid && tab[0] == "DELETE")
		type = DELETE;
	else if (valid)
		type = UNKNOWN;
	_parseUrl(tab[1]);
	if (valid && tab[2] != "HTTP/1.1")
		valid = false;
}

void Request::parse()
{
	_parseMethod();
	if (valid)
	{
		int pause;
		forup(i, 1, requestContent.size())
		{
			if (requestContent[i] == "{")
			{
				pause = ++i;
				break;
			}
			if (requestContent[i].find(':') != std::string::npos)
			{
				std::string key = std::string(requestContent[i].begin(), std::find(requestContent[i].begin(), requestContent[i].end(), ':') - 1);
				std::string value = std::string(std::find(requestContent[i].begin(), requestContent[i].end(), ':') + 1, requestContent[i].end());
				headers[key] = value;
			}
		}
		forup(i, pause, requestContent.size())
		{
			if (requestContent[i] == "}")
				break;
			// body.push_back(requestContent[i]);
		}
	}
}

std::string Request::getrawContent()
{
	return this->rawContent;
}

bool Request::getValid()
{
	return this->valid;
}

int Request::getType()
{
	return this->type;
}

int Request::getLocationIndex()
{
	return this->locationIndex;
}

std::string Request::getUrl()
{
	return this->url;
}

std::map<std::string, std::string> Request::getHeaders()
{
	return this->headers;
}

std::vector<char> Request::getBody()
{
	return this->body;
}

void Request::addRawContent(std::string rawContent)
{
	this->rawContent = rawContent;
	this->requestContent = _splitRawcontent(rawContent);
	forup(i, 0, requestContent.size())
		std::cout << requestContent[i] << std::endl;
}

Request::~Request()
{
	url.clear();
	headers.clear();
	requestContent.clear();
}