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
	bool bodyboundary;
	bool requestChunked;
	ServerConf serverConf;
	std::string url;
	std::string queryString;
	std::string absoluteUrl;
	std::string rawContent;
	std::string body;
	std::string boundary;
	std::vector<std::string> requestContent;
	std::vector<std::string> bodyParts;
	std::vector<std::string> bodyPartsFileNames;
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
	std::string &getUrl();
	std::string &getBody();
	std::string &getBoundary();
	std::string &getrawContent();
	std::string &getQueryString();
	std::string &getAbsoluteUrl();
	std::vector<std::string> &getRequestContent();
	std::vector<std::string> &getBodyParts();
	std::vector<std::string> &getBodyPartsFileNames();
	std::map<std::string, std::string> &getHeaders();

	// setters
	void setValidity(bool validity);
	void setBodyBoundary(bool bodyboundary);
	void setServerConf(ServerConf &serverConf);

	// class info
	bool bodyDoesExist();
	bool bodyBoundaryExist();
	bool isRequestChunked();
	bool empty();

	// class manipulation
	void clear();

	// parse methods
	void addRawContent(std::string rawContent);
	void parse();
	void parseMultiPartBody();
};

#endif