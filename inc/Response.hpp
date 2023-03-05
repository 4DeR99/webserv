#ifndef __RESPONSE_HPP__
#define __RESPONSE_HPP__

#include "inc.hpp"

enum StatusCode
{
	OK = 200,
	BAD_REQUEST = 400,
	UNAUTHORIZED = 401,
	NOT_FOUND = 404,
	INTERNAL_SERVER_ERROR = 500
};

class Response
{
private:
	size_t statusCode;
	Request request;
	ServerConf srvconf;
	std::string generatedResponse;

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
	void generateReponsetemplate(int statusCode);
	std::string getMessage(int statusCode);
	std::string getContentTypeString();
	std::string getContentType(std::string &extention);

	~Response();
};

#endif