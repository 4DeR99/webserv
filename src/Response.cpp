#include "inc.hpp"

Response::Response()
		: statusCode(0) {}

std::vector<std::string> Response::listDirectory(DIR *dir)
{
	std::vector<std::string> dirItems;

	// Read the directory entries
	struct dirent *entry;
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

	dirItems = listDirectory(dir);
	generatedResponse += "<!DOCTYPE html>\n";
	generatedResponse += "<html lang=\"en\">\n\n";
	generatedResponse += "<head>\n";
	generatedResponse += "\t<meta charset=\"UTF-8\">\n";
	generatedResponse += "\t<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
	generatedResponse += "\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
	generatedResponse += "\t<meta charset=\"UTF-8\">\n";
	generatedResponse += "\t<title>" + request.getUrl() + "</title>\n";
	generatedResponse += "</head>\n";

	generatedResponse += "<body >\n";
	for (size_t i = 0; i < dirItems.size(); i++)
	{
		generatedResponse += "\t<a href=\"" + '/' + split;
		generatedResponse += "\">" + dirItems[i] + "</a>"
	}

	generatedResponse += "</body>\n\n";
	generatedResponse += "</html>\n";
}

Response::Response(Request &request, ServerConf &serverconf)
		: statusCode(0),
			request(request),
			srvconf(serverconf) {}

void Response::getAction()
{
	std::string url = request.getUrl();

	Location location;
	try
	{
		location = srvconf.getLocation(request.getLocationIndex());
	}
	catch (const std::exception &e)
	{
		generateReponsetemplate(NOT_FOUND);
		return;
	}

	DIR *dir = opendir(url.c_str());

	if (!location.getIndex().empty())
		url = location.getIndex();
	else if (dir)
	{
		generateBasedOnDirectory(dir);

		return;
	}
	std::fstream fs(url);
	if (!fs.good())
	{
		generateFileError(fs);
		return;
	}
	generateReponsetemplate(OK);
	std::string buffer;
	while (getline(fs, buffer, '\n'))
		generatedResponse += buffer;
	fs.close();
	generatedResponse += "\r\n";
}

void Response::postAction()
{
	std::string url = request.getUrl();
	std::fstream fs(url);

	if (!fs.good())
	{
		generateFileError(fs);
		return;
	}
	for (size_t i = 0; i < request.getBody().size(); i++)
		fs << request.getBody()[i];
	fs.close();
	generateReponsetemplate(OK);
}

void Response::deleteAction()
{
	// pass
}

void Response::generateFileError(std::fstream &fs)
{
	if (errno == ENOENT)
		generateReponsetemplate(NOT_FOUND);
	else if (errno == EACCES)
		generateReponsetemplate(UNAUTHORIZED);
	else
		generateReponsetemplate(INTERNAL_SERVER_ERROR);
}

void Response::generateErrorMessage()
{
	std::map<int, std::string> errPages = srvconf.getErr_page();
	std::map<int, std::string> defaultErrPages = srvconf.getDefaultErrPage();
	std::fstream fs;
	std::string buff;

	if (!errPages[statusCode].empty())
	{
		fs.open(errPages[statusCode]);
		while (getline(fs, buff, '\n'))
			generatedResponse += buff;
		generatedResponse += "\r\n";
	}
	else
	{
		fs.open(defaultErrPages[statusCode]);
		while (getline(fs, buff, '\n'))
			generatedResponse += buff;
		generatedResponse += "\r\n";
	}
	fs.close();
}

void Response::generateResponse()
{
	if (!request.getValid())
		generateReponsetemplate(BAD_REQUEST);
	else if (request.getType() == GET)
		getAction();
	else if (request.getType() == POST)
		postAction();
	else if (request.getType() == DELETE)
		deleteAction();
	if (statusCode > 200)
		generateErrorMessage();
	generatedResponse += "\r\n";
}

std::vector<std::string> Response::_split(std::string s, char c)
{
	std::string buff;
	std::stringstream str_str(s);
	std::vector<std::string> arr;
	while (getline(str_str, buff, c))
		arr.push_back(buff);
	return arr;
}

std::string Response::getMessage(int statusCode)
{
	switch (statusCode)
	{
	case OK:
		return "OK";
	case NOT_FOUND:
		return "NOT_FOUND";
	case BAD_REQUEST:
		return "BAD_REQUEST";
	default:
		return "CHANGE_ME_LATER";
	}
}

std::string Response::getContentType(std::string &extention)
{
	if (extention == "html")
		return "text/html";
	else if (extention == "css")
		return "text/css";
	else if (extention == "json")
		return "application/json";
	else if (extention == "xml")
		return "application/xml";
	else if (extention == "png")
		return "image/png";
	else if (extention == "jpeg")
		return "image/jpeg";
	else if (extention == "mpeg")
		return "audio/mpeg";
	return "text/plain";
}

std::string Response::getContentTypeString()
{
	std::string contentTypeString, contentType;
	std::string url = this->request.getUrl();

	std::vector<std::string> dottedSplit = _split(url, '.');
	if (dottedSplit.size() == 1)
		contentType = "text/plain";
	else
		contentType = getContentType(dottedSplit.back());
	contentTypeString = "Content-Type: " + contentType;
	return contentTypeString;
}

void Response::generateReponsetemplate(int statusCode)
{
	this->statusCode = statusCode;
	generatedResponse += "HTTP/1.1 " + std::to_string(statusCode) + " " + getMessage(statusCode) + "\r\n";
	generatedResponse += getContentTypeString() + "\r\n";
	generatedResponse += "Content-Length " + std::to_string(fileContent.size()) + "\r\n";
}

Response::~Response() {}