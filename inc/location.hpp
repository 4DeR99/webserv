#ifndef __LOCATION_HPP__
#define __LOCATION_HPP__
#include "inc.hpp"

class location
{
private:
	std::string path, root, upload_path, index, cgi_info, ret_path, redir_path;
	int autoindex_c, ret_n, redir_n;
	bool autoindex;
	std::vector<std::string> allow_methods;

public:
	location();
	// setters
	void _setPath(std::string s);
	void _setRoot(std::string s);
	void _setUploadPath(std::string s);
	void _setIndex(std::string s);
	void _setAutoIndex(bool status);
	void _setAllowMethods(std::vector<std::string> methods);
	void _setCgi(std::string cgi);
	void _setRedirection(int n, std::string s);
	void _setReturn(int n, std::string);
	// geters
	std::string _getPath();
	std::string _getRoot();
	std::string _getUploadpath();
	std::string _getIndex();
	std::string _getCgi();
	std::string _getRet_path();
	int _getRet_n();
	std::string _getRedir_path();
	int _getRedir_n();
	std::vector<std::string> _getmethods();
	//location reset
	void	clear();
	//location tests
	bool empty();
	
	~location();
};

#endif