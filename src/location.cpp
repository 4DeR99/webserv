#include "inc.hpp"

Location::Location()
		: autoindexCount(-1),
			returnNb(-1),
			redirectionNb(-1)
{
}

void Location::setPath(std::string path)
{
	if (!path.empty())
		throw std::invalid_argument(DOUBLE_PATH);
	this->path = path;
}

void Location::setRoot(std::string root)
{
	if (!root.empty())
		throw std::invalid_argument(DOUBLE_ROOT);
	this->root = root;
}

void Location::setUploadPath(std::string uploadPath)
{
	if (!uploadPath.empty())
		throw std::invalid_argument(DOUBLE_UPLOADPATH);
	this->uploadPath = uploadPath;
}

void Location::setIndex(std::string index)
{
	if (!index.empty())
		throw std::invalid_argument(DOUBLE_INDEX);
	this->index = index;
}

void Location::setAutoIndex(bool status)
{
	if (autoindexCount != -1)
		throw std::invalid_argument(DOUBLE_AUTOINDEX);
	this->autoindexCount++;
	this->autoindex = status;
}

void Location::setAllowMethods(std::vector<std::string> methods)
{
	if (!allowMethods.empty())
		throw std::invalid_argument(DOUBLE_ALLOWMETHODS);
	this->allowMethods = methods;
}

void Location::setRedirection(int nb, std::string path)
{
	if (redirectionNb != -1)
		throw std::invalid_argument(DOUBLE_REDIRECTION);
	this->redirectionNb = nb;
	this->redirectionPath = path;
}

void Location::setReturn(int nb, std::string path)
{
	if (returnNb != -1)
		throw std::invalid_argument(DOUBLE_RETURN);
	this->returnNb = nb;
	this->returnPath = path;
}

void Location::setCgi(std::string cgi)
{
	if (!cgiInfo.empty())
		throw std::invalid_argument(DOUBLE_CGI);
	cgiInfo = cgi;
}

std::string Location::getPath()
{
	return this->path;
}

std::string Location::getRoot()
{
	return this->root;
}

std::string Location::getUploadpath()
{
	return this->uploadPath;
}

std::string Location::getIndex()
{
	return this->index;
}

std::string Location::getCgi()
{
	return this->cgiInfo;
}

std::string Location::getReturnPath()
{
	return this->returnPath;
}

std::string Location::getRedirectionPath()
{
	return this->redirectionPath;
}

int Location::getReturnNb()
{
	return this->returnNb;
}

int Location::getRedirectionNb()
{
	return this->redirectionNb;
}

std::vector<std::string> Location::getmethods()
{
	return this->allowMethods;
}

bool Location::empty()
{
	return (path.empty() && root.empty() && uploadPath.empty() && index.empty() && cgiInfo.empty() && returnPath.empty() && redirectionPath.empty() && allowMethods.empty() && autoindexCount == -1 && returnNb == -1 && redirectionNb == -1);
}

void Location::clear()
{
	path.clear();
	root.clear();
	uploadPath.clear();
	index.clear();
	cgiInfo.clear();
	returnPath.clear();
	redirectionPath.clear();
	allowMethods.clear();
	autoindexCount = -1;
	returnNb = -1;
	redirectionNb = -1;
}

Location::~Location()
{
	allowMethods.clear();
	cgiInfo.clear();
}