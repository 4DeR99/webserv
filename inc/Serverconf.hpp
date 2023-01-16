#ifndef __SERVERCONF_HPP__
#define __SERVERCONF_HPP__
#include "server.hpp"

class ServerConf
{
private:
	int port;
	std::string server_name, root, host;
	int client_max_bodt_size;
	std::map<int, std::string> err_page;
	// std::vector<>

public:
	ServerConf();
	void _setPort(int n);
	void _setSrvName(std::string s);
	void _setRoot(std::string s);
	void _setUploadPath(std::string s);
	void _setHost(std::string s);
	void _addErrPage(int nb, std::string s);
	~ServerConf();
};

#endif