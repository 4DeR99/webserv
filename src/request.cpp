#include "inc.hpp"

Request::Request() : valid(true), type(UNKNOWN)
{
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

void Request::_parse_method()
{
	std::vector<std::string> tab = _split(requestContent[0], ' ');
	if (tab.size() != 3)
		valid = false;
	forup(i, 0, tab[0].size())
	{
		if (islower(tab[0][i]))
			valid = false;
	}
	if (tab[0] == "GET")
		type = GET;
	if (tab[0] == "POST")
		type = POST;
	if (tab[0] == "DELETE")
		type = DELETE;
	else
		type = UNKNOWN;
	if (tab[1].front() != '/' || tab[1].find("/../") == std::string::npos)
		valid = false;
	if (tab[2] != "HTTP/1.1")
		valid = false;
}

void Request::parse()
{
	_parse_method();
	if (valid)
	{
		int pause;
		forup(i, 0, requestContent.size())
		{
			if (requestContent[i] == "{")
			{
				pause = ++i;
				break;
			}
			if (requestContent[i].find(':') != std::string::npos)
			{
				headers[std::string(requestContent.begin(), std::find(requestContent.begin(), requestContent.end(), ':') - 1)] = std::string(std::find(requestContent.begin(), requestContent.end(), ':') + 1, requestContent.end());
			}
		}
		forup(i, pause, requestContent.size())
		{
			if (requestContent[i] == "}")
				break;
			body.push_back(requestContent[i]);
		}
	}
}

void Request::getRawContent(std::string rawContent)
{
	this->rawContent = rawContent;
}

Request::~Request()
{
	url.clear();
	headers.clear();
	requestContent.clear();
}