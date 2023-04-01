#ifndef __REQUEST_HPP__
#define __REQUEST_HPP__

#include "Inc.hpp"
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
	bool bodyExist;
	bool requestChunked;
	int type;
	int locationIndex;
	int bodyLength;
	std::string url;
	std::string absoluteUrl;
	std::string rawContent;
	std::map<std::string, std::string> headers;
	ServerConf serverConf;

	void _parseMethod();
	void _parseUrl(std::string &url);
	void _sweep(std::string &string);
	std::vector<std::string> _split(std::string s, char c);
	std::vector<std::string> _splitRawcontent(std::string s);

public:
	Request();
	Request(ServerConf &serverConf);
	Request(Request const &_2Copy);
	Request &operator=(Request const &_2Copy);
	~Request();

	// getters
	bool isValid();
	int getType();
	int getLocationIndex();
	int getBodyLength();
	std::string getrawContent();
	std::string getUrl();
	std::string getAbsoluteUrl();
	std::map<std::string, std::string> getHeaders();
	std::vector<char> getBody();

	// setters
	void setValidity(bool validity);
	void setServerConf(ServerConf &serverConf);

	// class info
	bool
	bodyDoesExist();
	bool isRequestChunked();
	bool empty();

	void clear();

	void addRawContent(std::string rawContent);
	void parse();
};

#endif