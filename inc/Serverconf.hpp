#ifndef __SERVERCONF_HPP__
#define __SERVERCONF_HPP__
#include "server.hpp"

class ServerConf
{
private:
	std::map<std::string, int> listen;
	std::string server_name, root, upload_path;
	bool autoindex;
	std::vector<std::string> methods, index;
	int client_body_limit;
	std::map<int, std::string> err_page;
	std::vector<std::vector<std::string>> ServData;

public:
	ServerConf(std::vector<std::string> &ServContent);
	~ServerConf();
};

#endif