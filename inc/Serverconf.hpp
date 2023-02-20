#ifndef __SERVERCONF_HPP__
#define __SERVERCONF_HPP__
#include "inc.hpp"

class ServerConf
{
private:
	int sd, on;
	std::string port, host, server_name, root;
	int client_max_bodt_size;
	std::map<int, std::string> err_page;
	std::vector<location> loc;
	std::map<std::string, int> l_path;
	struct addrinfo hints, *res;

public:
	ServerConf();
	//setters
	void _setPort(std::string n);
	void _setSrvName(std::string s);
	void _setRoot(std::string s);
	void _setHost(std::string s);
	void _addErrPage(int nb, std::string s);
	void _setCMBZ(int CMBZ);
	void _addLocation(location l);
	//geters
	std::string _getPort();
	std::string _getSrvname();
	std::string _getRoot();
	int _getCMBZ();
	std::string _getHost();
	std::map<int, std::string> _getErr_page();
	std::vector<location> _getLocation();
	int	_getSd();
	//socket management
	void createSd();
	void bindSd();
	void listenSd();
	//reset srv
	void clear();
	~ServerConf();
};

#endif