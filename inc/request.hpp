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
	int type;
	int bodyLength;
	int locationIndex;
	bool valid;
	bool bodyExist;
	bool requestChunked;
	ServerConf serverConf;
	std::string url;
	std::string absoluteUrl;
	std::string rawContent;
	std::vector<char> body;
	std::vector<std::string> requestContent;
	std::map<std::string, std::string> headers;

	// private methods
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
	int getType();
	int getLocationIndex();
	int getBodyLength();
	bool isValid();
	std::string getUrl();
	std::string getAbsoluteUrl();
	std::string getrawContent();
	std::vector<char>& getBody();
	std::vector<std::string>& getRequestContent();
	std::map<std::string, std::string> getHeaders();

	// setters
	void setValidity(bool validity);
	void setServerConf(ServerConf &serverConf);

	// class info
	bool bodyDoesExist();
	bool isRequestChunked();
	bool empty();

	// class manipulation
	void clear();

	// parse methods
	void addRawContent(std::string rawContent);
	void parse();
};

#endif