#ifndef __LOCATION_HPP__
#define __LOCATION_HPP__
#include "Inc.hpp"

class Location
{
private:
	std::string path;
	std::string root;
	std::string uploadPath;
	std::string index;
	std::string cgiInfo;
	// std::string returnPath;
	std::string redirectionPath;
	int autoindexCount;
	int returnNb;
	int redirectionNb;
	bool autoindex;
	std::vector<std::string> allowMethods;

public:
	Location();
	Location(Location const &_2Copy);
	Location& operator=(Location const &_2Copy);
	~Location();

	// getters
	std::vector<std::string> getMethods();
	std::string& getRedirectionPath();
	std::string& getUploadpath();
	std::string& getIndex();
	std::string& getPath();
	std::string& getRoot();
	std::string& getCgi();
	// std::string getReturnPath();
	int getRedirectionNb();
	int getReturnNb();
	int getAutoIndex();

	// setters
	void setAllowMethods(std::vector<std::string> methods);
	void setRedirection(int nb, std::string path);
	void setUploadPath(std::string uploadPath);
	// void setReturn(int nb, std::string path);
	void setIndex(std::string index);
	void setPath(std::string path);
	void setRoot(std::string root);
	void setAutoIndex(bool status);
	void setCgi(std::string cgi);

	void clear();

	bool empty();

};

#endif