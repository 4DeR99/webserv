#ifndef __LOCATION_HPP__
#define __LOCATION_HPP__
#include "inc.hpp"

class location
{
private:
	std::string path, root, upload_path, index;
	int autoindex_c;
	bool autoindex;
	std::vector<std::string> allow_methods, cgi_info;
	std::map<int, std::string> redirection, ret;

public:
	location();
	void _setPath(std::string s);
	void _setRoot(std::string s);
	void _setUploadPath(std::string s);
	void _setIndex(std::string s);
	void _setAutoIndex(bool status);
	void _setAllowMethods(std::vector<std::string> methdods);
	void _setCgi(std::vector<std::string> cgi);
	void _addRedirection(int n, std::string s);
	void _addReturn(int n, std::string)
	~location();
};

#endif