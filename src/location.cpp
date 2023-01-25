#include "location.hpp"

location::location() : autoindex_c(-1), ret_n(-1), redir_n(-1)
{
}

void location::_setPath(std::string s)
{
	if (!path.empty())
		throw std::invalid_argument(DOUBLE_PATH);
	path = s;
}

void location::_setRoot(std::string s)
{
	if (!root.empty())
		throw std::invalid_argument(DOUBLE_ROOT);
	root = s;
}

void location::_setUploadPath(std::string s)
{
	if (!upload_path.empty())
		throw std::invalid_argument(DOUBLE_UPLOADPATH);
	upload_path = s;
}

void location::_setIndex(std::string s)
{
	if (!index.empty())
		throw std::invalid_argument(DOUBLE_INDEX);
	index = s;
}

void location::_setAutoIndex(bool status)
{
	if (autoindex_c != -1)
		throw std::invalid_argument(DOUBLE_AUTOINDEX);
	autoindex_c++;
	autoindex = status;
}

void location::_setAllowMethods(std::vector<std::string> methods)
{
	if (!allow_methods.empty())
		throw std::invalid_argument(DOUBLE_ALLOWMETHODS);
	allow_methods = methods;
}

void location::_setRedirection(int n, std::string s)
{
	if (redir_n != -1)
		throw std::invalid_argument(DOUBLE_REDIRECTION);
	redir_n = n;
	redir_path = s;
}

void location::_setReturn(int n, std::string s)
{
	if (ret_n != -1)
		throw std::invalid_argument(DOUBLE_RETURN);
	ret_n = n;
	ret_path = s;
}

void location::_setCgi(std::string cgi)
{
	if (!cgi_info.empty())
		throw std::invalid_argument(DOUBLE_CGI);
	cgi_info = cgi;
}

std::string location::_getPath()
{
	return path;
}

std::string location::_getRoot()
{
	return root;
}

std::string location::_getUploadpath()
{
	return upload_path;
}

std::string location::_getIndex()
{
	return index;
}

std::string location::_getCgi()
{
	return cgi_info;
}

std::string location::_getRet_path()
{
	return ret_path;
}

std::string location::_getRedir_path()
{
	return redir_path;
}

int location::_getRet_n()
{
	return ret_n;
}

int location::_getRedir_n()
{
	return redir_n;
}

std::vector<std::string> location::_getmethods()
{
	return allow_methods;
}

bool location::empty(){
	return (path.empty() && root.empty() && upload_path.empty() && index.empty() && cgi_info.empty()
		&& ret_path.empty() && redir_path.empty() && allow_methods.empty() && autoindex_c == -1
		&& ret_n == -1 && redir_n == -1);
}

void	location::clear()
{
	path.clear();
	root.clear();
	upload_path.clear();
	index.clear();
	cgi_info.clear();
	ret_path.clear();
	redir_path.clear();
	allow_methods.clear();
	autoindex_c = -1;
	ret_n = -1;
	redir_n = -1;
}

location::~location()
{
	allow_methods.clear();
	cgi_info.clear();
}