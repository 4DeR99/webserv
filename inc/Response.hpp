#ifndef __RESPONSE_HPP__
#define __RESPONSE_HPP__

#include "Inc.hpp"

enum StatusCode
{
	OK = 200,
	BAD_REQUEST = 400,
	FORBIDDEN = 403,
	NOT_FOUND = 404,
	NOT_ALLOWED = 405,
	INTERNAL_SERVER_ERROR = 500,
	CGI = 600
};

class Response
{
private:
	size_t statusCode;
	size_t dirListen;
	Request request;
	ServerConf srvconf;
	std::string generatedResponse;
	std::string generatedBody;

	// private functions
	std::vector<std::string> _split(std::string s, char c);

public:
	Response();
	// Response(Request &request, ServerConf &serverconf);
	Response &operator=(Response const &_2Copy);

	// error
	void generateFileError(std::fstream &fs);
	void generateErrorMessage();
	std::vector<std::string> listDirectory(DIR *dir);

	// actions: get
	void getAction();
	void generateBasedOnDirectory(DIR *dir);

	// actions: post
	void postAction();

	// actions: delete
	void deleteAction();

	// main
	void generateResponse(Request &request, ServerConf &serverConf);

	// utils to generate reponse
	void generateResponsetemplate();
	std::string getMessage(int statusCode);
	std::string getContentTypeString();
	std::string getContentType(std::string &extention);
	std::string getGeneratedResponse();
	std::string getBody();

	void clear();

	~Response();
};

#endif