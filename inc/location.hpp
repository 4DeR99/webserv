#ifndef __LOCATION_HPP__
#define __LOCATION_HPP__
#include "inc.hpp"

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

	std::string getPath();
	std::string getRoot();
	std::string getUploadpath();
	std::string getIndex();
	std::string getCgi();
	std::string getReturnPath();
	int getReturnNb();
	std::string getRedirectionPath();
	int getRedirectionNb();
	std::vector<std::string> getmethods();

	void setPath(std::string path);
	void setRoot(std::string root);
	void setUploadPath(std::string uploadPath);
	void setIndex(std::string index);
	void setAutoIndex(bool status);
	void setAllowMethods(std::vector<std::string> methods);
	void setCgi(std::string cgi);
	void setRedirection(int nb, std::string path);
	void setReturn(int nb, std::string path);

	void clear();

	bool empty();

};

#endif