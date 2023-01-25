#ifndef __SERVERCONF_HPP__
#define __SERVERCONF_HPP__
#include "server.hpp"
#include "location.hpp"

class ServerConf
{
private:
	int port;
	std::string server_name, root;
	int client_max_bodt_size;
	std::vector<int> host;
	std::map<int, std::string> err_page;
	std::vector<location> loc;
	std::map<std::string, int> l_path;

public:
	ServerConf();
	//setters
	void _setPort(int n);
	void _setSrvName(std::string s);
	void _setRoot(std::string s);
	void _setHost(std::vector<int> s);
	void _addErrPage(int nb, std::string s);
	void _setCMBZ(int CMBZ);
	void _addLocation(location l);
	//geters
	int _getPort();
	std::string _getSrvname();
	std::string _getRoot();
	int _getCMBZ();
	std::vector<int> _getHost();
	std::map<int, std::string> _getErr_page();
	std::vector<location> _getLocation();
	//reset srv
	void clear();
	~ServerConf();
};

#endif