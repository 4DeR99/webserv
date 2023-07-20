#include "Inc.hpp"

Response::Response()
		:	responseCompleted(false),
			statusCode(0),
			dirListen(0) {}

//! check this later
// Response::Response(Request &request, ServerConf &serverconf)
// 		: statusCode(0),
// 			request(request),
// 			srvconf(serverconf) {}

std::vector<std::string> Response::_split(std::string s, char c)
{
	std::string buff;
	std::stringstream str_str(s);
	std::vector<std::string> arr;
	while (getline(str_str, buff, c))
		arr.push_back(buff);
	return arr;
}

std::vector<std::string> Response::listDirectory(DIR *dir)
{
	std::vector<std::string> dirItems;

	// Read the directory entries
	struct dirent *entry = NULL;
	while ((entry = readdir(dir)) != NULL)
	{
		std::string name = entry->d_name;
		if (name != "." && name != "..")
		{
			dirItems.push_back(name);
		}
	}

	// Close the directory
	closedir(dir);
	return dirItems;
}

void Response::generateBasedOnDirectory(DIR *dir)
{
	std::vector<std::string> dirItems;
	std::string url = request.getUrl();
	if (url[url.size() - 1] != '/')
		url += '/';
	dirItems = listDirectory(dir);
	generatedBody += "<!DOCTYPE html>\n";
	generatedBody += "<head>\n";
	generatedBody += "\t<title>" + request.getUrl() + "</title>\n";
	generatedBody += "</head>\n";
	generatedBody += "<h1>Index of " + request.getUrl() + "</h1>\n";
	generatedBody += "<hr>\n";
	generatedBody += "<body >\n";
	for (size_t i = 0; i < dirItems.size(); i++)
	{
		if (dirItems[i][0] == '.')
			continue;
		generatedBody += "\t<a href=\"" + url + dirItems[i];
		generatedBody += "\">" + dirItems[i] + "</a>";
		generatedBody += "<br>\n";
	}
	generatedBody += "</body>\n\n";
	generatedBody += "</html>\n";
}

void Response::generateFileError(std::fstream &fs)
{
	(void)fs;
	if (errno == ENOENT)
		this->statusCode = NOT_FOUND;
	else if (errno == EACCES)
		this->statusCode = FORBIDDEN;
	else
		this->statusCode = INTERNAL_SERVER_ERROR;
}

int Response::_cgi()
{
	try {
		generatedBody = execCgi(request, srvconf, location);
		statusCode = OK;
	}
	catch(const std::exception& e) {
		statusCode = INTERNAL_SERVER_ERROR;
		return -1;
	}
	return 0;
}

void Response::getAction()
{
	std::string url = this->request.getAbsoluteUrl();
	bool cgi = url.substr(url.find_last_of('.') + 1) == "php" || url.substr(url.find_last_of('.') + 1) == "py";
	DIR *dir = opendir(this->request.getAbsoluteUrl().c_str());
	if (!location.getIndex().empty())
		url = location.getIndex();
	else if (dir) {
		// directory listing
		if (!location.getAutoIndex())
		{
			this->statusCode = FORBIDDEN;
			return;
		}
		generateBasedOnDirectory(dir);
		dirListen = 1;
		this->statusCode = OK;
		return;
	}
	std::fstream fs(url.c_str());
	if (!fs.good()) {
		// file error
		generateFileError(fs);
		return;
	}
	if (!location.getCgi().empty() && cgi)
		_cgi();
	else {
		this->statusCode = OK;
		std::string buffer;
		while (getline(fs, buffer, '\n'))
		{
			generatedBody += buffer;
			generatedBody += "\n";
		}
		generatedBody += "\n";
		fs.close();
	}
}

void Response::postAction()
{
	// std::string url = request.getUrl();
	// std::fstream fs(url);

	// if (!fs.good())
	// {
	// 	generateFileError(fs);
	// 	return;
	// }
	// for (size_t i = 0; i < request.getBody().size(); i++)
	// 	fs << request.getBody()[i];
	// fs.close();
	// generateResponsetemplate(OK);
}

void Response::deleteAction()
{
	// pass
}

void Response::generateErrorMessage()
{
	std::map<int, std::string> errPages = srvconf.getErr_page();
	std::fstream fs;
	std::string buff;

	fs.open(errPages[this->statusCode]);
	if (fs.good())
	{
		while (getline(fs, buff, '\n'))
		{
			generatedBody += buff;
			generatedBody += "\n";
		}
		generatedBody += "\n";
		fs.close();
	}
}

std::string Response::getMessage()
{
	switch (this->statusCode)
	{
		case OK:
			return "OK";
		case BAD_REQUEST:
			return "BAD REQUEST";
		case FORBIDDEN:
			return "FORBIDDEN";
		case NOT_FOUND:
			return "NOT FOUND";
		case NOT_ALLOWED:
			return "NOT ALLOWED";
		default:
			return "INTERNAL SERVER ERROR";
	}
}

std::string Response::getContentType(std::string &extention)
{if (extention == "html")
		return "text/html";
	else if (extention == "css")
		return "text/css";
	else if (extention == "json")
		return "application/json";
	else if (extention == "xml")
		return "application/xml";
	else if (extention == "png")
		return "image/png";
	else if (extention == "jpeg" || extention == "jpg")
		return "image/jpeg";
	else if (extention == "mpeg")
		return "audio/mpeg";
	else if (extention == "mp4")
		return "video/mp4";
	else if (extention == "php" || extention == "py")
		return "text/html";
	return "text/plain";
}

std::string Response::getContentTypeString()
{
	std::string contentTypeString, contentType;
	std::string url = this->request.getUrl();

	std::vector<std::string> dottedSplit = _split(url, '.');
	if (dirListen || this->statusCode != OK)
		contentType = "text/html";
	else if (dottedSplit.size() == 1)
		contentType = "text/plain";
	else
		contentType = getContentType(dottedSplit.back());
	contentTypeString = "Content-Type: " + contentType;
	return contentTypeString;
}

void Response::generateResponsetemplate()
{
	generatedResponse += "HTTP/1.1 " + std::to_string(statusCode) + " " + getMessage() + "\r\n";
	generatedResponse += getContentTypeString() + "\r\n";
	generatedResponse += "Content-Length: " + std::to_string(generatedBody.size()) + "\r\n";
	generatedResponse += "Connection: close\r\n";
	generatedResponse += "\r\n";
	generatedResponse += generatedBody;
	generatedResponse += "\r\n";
}

int Response::getappropiateLocation()
{
	try {
		this->location = srvconf.getLocation(request.getLocationIndex());
	}
	catch (const std::exception &e) {
		return -1;
	}
	return 0;
}

void Response::generateResponse(Request &request, ServerConf &serverConf)
{
		
	this->request = request;
	this->srvconf = serverConf;
	if (getappropiateLocation() < 0)
		this->statusCode = NOT_FOUND;
	else if (!request.isValid())
		this->statusCode = BAD_REQUEST;
	else if (request.getType() == GET)
		getAction();
	else if (request.getType() == POST)
		postAction();
	// else if (request.getType() == DELETE)
	// 	deleteAction();
	if (statusCode > OK)
		generateErrorMessage();
	generateResponsetemplate();
	this->responseCompleted = true;
}

bool Response::isResponseCompleted() { return responseCompleted; }

void Response::clear()
{
	generatedResponse.clear();
	generatedBody.clear();
	statusCode = 0;
	dirListen = 0;
	responseCompleted = false;
	request.clear();
}

std::string& Response::getGeneratedResponse() { return generatedResponse; }

Location& Response::getLocation() { return location; }

Response::~Response() {}