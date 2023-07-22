#include "Inc.hpp"

Location::Location()
		: autoindexCount(-1),
			returnNb(-1),
			autoindex(false) {}

Location::Location(Location const &_2Copy) { this->operator=(_2Copy); }

Location &Location::operator=(Location const &_2Copy)
{
	this->path = _2Copy.path;
	this->root = _2Copy.root;
	this->uploadPath = _2Copy.uploadPath;
	this->index = _2Copy.index;
	this->cgiInfo = _2Copy.cgiInfo;
	this->returnPath = _2Copy.returnPath;
	this->returnNb = _2Copy.returnNb;
	// this->redirectionPath = _2Copy.redirectionPath;
	this->autoindexCount = _2Copy.autoindexCount;
	// this->redirectionNb = _2Copy.redirectionNb;
	this->autoindex = _2Copy.autoindex;
	this->allowMethods = _2Copy.allowMethods;
	return *this;
}

Location::~Location()
{
	allowMethods.clear();
	cgiInfo.clear();
}

void Location::setPath(std::string path)
{
	if (!this->path.empty())
		throw std::invalid_argument(DOUBLE_PATH);
	this->path = path;
}

void Location::setRoot(std::string root)
{
	if (!this->root.empty())
		throw std::invalid_argument(DOUBLE_ROOT);
	this->root = root;
}

void Location::setUploadPath(std::string uploadPath)
{
	if (!this->uploadPath.empty())
		throw std::invalid_argument(DOUBLE_UPLOADPATH);
	this->uploadPath = uploadPath;
}

void Location::setIndex(std::string index)
{
	if (!this->index.empty())
		throw std::invalid_argument(DOUBLE_INDEX);
	this->index = index;
}

void Location::setAutoIndex(bool status)
{
	if (this->autoindexCount != -1)
		throw std::invalid_argument(DOUBLE_AUTOINDEX);
	this->autoindexCount++;
	this->autoindex = status;
}

void Location::setAllowMethods(std::vector<std::string> methods)
{
	if (!this->allowMethods.empty())
		throw std::invalid_argument(DOUBLE_ALLOWMETHODS);
	this->allowMethods = methods;
}

// void Location::setRedirection(int nb, std::string path)
// {
// 	if (this->redirectionNb != -1)
// 		throw std::invalid_argument(DOUBLE_REDIRECTION);
// 	this->redirectionNb = nb;
// 	this->redirectionPath = path;
// }

void Location::setReturn(int nb, std::string path)
{
	if (returnNb != -1)
		throw std::invalid_argument(DOUBLE_RETURN);
	this->returnNb = nb;
	this->returnPath = path;
}

void Location::setCgi(std::string cgi)
{
	if (!this->cgiInfo.empty())
		throw std::invalid_argument(DOUBLE_CGI);
	cgiInfo = cgi;
}

std::string& Location::getPath() { return this->path; }

std::string& Location::getRoot() { return this->root; }

std::string& Location::getUploadpath() { return this->uploadPath; }

std::string& Location::getIndex() { return this->index; }

std::string& Location::getCgi() { return this->cgiInfo; }

std::string& Location::getReturnPath() { return this->returnPath; }

int Location::getReturnNb() { return this->returnNb; }

int Location::getAutoIndex() { return this->autoindex; }

std::vector<std::string> Location::getMethods() { return this->allowMethods; }

bool Location::empty()
{
	return (path.empty() && root.empty() && uploadPath.empty() && index.empty() && cgiInfo.empty() && allowMethods.empty() && autoindexCount == -1 && returnNb == -1);
}

void Location::clear()
{
	path.clear();
	root.clear();
	uploadPath.clear();
	index.clear();
	cgiInfo.clear();
	returnPath.clear();
	allowMethods.clear();
	autoindexCount = -1;
	returnNb = -1;
	autoindex = false;
}