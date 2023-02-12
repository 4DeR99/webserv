#include "request.hpp"

request::request(std::vector<std::string> requestContent) : valid(false), type(UNKNOWN)
{
}

void request::parse()
{
	
}

request::~request()
{
	url.clear();
	headers.clear();
}