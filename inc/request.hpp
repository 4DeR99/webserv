#ifndef __REQUEST_HPP__
#define __REQUEST_HPP__

#include "inc.hpp"

enum request_type
{
	GET,
	POST,
	DELETE,
	UNKNOWN
};

class Request
{
private:
	std::vector<std::string> requestContent;
	std::vector<char> body;
	bool valid;
	int type;
	std::string url;
	std::string rawContent;
	std::map<std::string, std::string> headers;
	void _parse_method();
	std::vector<std::string> _split(std::string s, char c);
	std::vector<std::string> _splitRawcontent(std::string s);

public:
	Request();
	Request(Request const &_2Copy);
	Request &operator=(Request const &_2Copy);
	~Request();

	std::string _getrawContent();
	bool getValid();
	int getType();
	std::string getUrl();
	std::map<std::string, std::string> getHeaders();
	std::vector<char> getBody();

	void addRawContent(std::string rawContent);
	void parse();
};

#endif