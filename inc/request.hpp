#ifndef __REQUEST_HPP__
#define __REQUEST_HPP__

#include "inc.hpp"

enum request_type {
	GET,
	POST,
	DELETE,
	UNKNOWN
};

class Request
{
private :
	std::vector<std::string> requestContent, body;
	bool valid;
	int type;
	std::string url;
	std::map<std::string, std::string> headers;
	void _parse_method();
	std::vector<std::string> _split(std::string s, char c);
public :
	Request();
	void parse();
	~Request();
};

#endif