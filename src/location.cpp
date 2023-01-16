#include "location.hpp"

location::location() : autoindex_c(-1)
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
	if (autoindex_c == -1)
		throw std::invalid_argument(DOUBLE_AUTOINDEX);
	autoindex = status;
}

void location::_addRedirection(int n, std::string s)
{
}

location::~location()
{
	allow_methods.clear();
	cgi_info.clear();
	redirection.clear();
	ret.clear();
}