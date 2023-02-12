#ifndef __REQUEST_HPP__
#define __REQUEST_HPP__

#include "parser.hpp"

enum request_type {
	GET,
	POST,
	DELETE,
	UNKNOWN
};

class request
{
private :
	bool valid;
	int type;
	std::string url;
	std::map<std::string, std::string> headers;
public :
	request(std::vector<std::string> requestContent);
	void parse();
	~request();
};

#endif