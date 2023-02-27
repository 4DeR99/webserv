#ifndef __REQUEST_HPP__
#define __REQUEST_HPP__

#include "inc.hpp"
#define NO_LOCATION -1

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
	int type, locationIndex;
	std::string url;
	std::string rawContent;
	std::map<std::string, std::string> headers;
	ServerConf serverConf;

	void _parseMethod();
	void _parseUrl(std::string &url);
	std::vector<std::string> _split(std::string s, char c);
	std::vector<std::string> _splitRawcontent(std::string s);

public:
	Request();
	Request(ServerConf &serverConf);
	Request(Request const &_2Copy);
	Request &operator=(Request const &_2Copy);
	~Request();

	// getters
	bool getValid();
	int getType();
	int getLocationIndex();
	std::string getrawContent();
	std::string getUrl();
	std::map<std::string, std::string> getHeaders();
	std::vector<char> getBody();

	void addRawContent(std::string rawContent);
	void parse();
};

#endif