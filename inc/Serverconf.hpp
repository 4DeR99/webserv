#ifndef __SERVERCONF_HPP__
#define __SERVERCONF_HPP__
#include "inc.hpp"

class ServerConf
{
private:
	std::string port, host, serverName, root;
	int clientMaxBodySize;
	std::map<int, std::string> errorPage, defaultErrPage;
	std::vector<Location> locations;
	std::map<std::string, int> locationsPath;

	int sd, on;
	struct addrinfo hints, *res;

public:
	ServerConf();
	ServerConf(ServerConf const &_2Copy);
	ServerConf &operator=(ServerConf const &_2Copy);
	~ServerConf();

	// setters
	void setPort(std::string port);
	void setSrvName(std::string srvname);
	void setRoot(std::string root);
	void setHost(std::string host);
	void addErrPage(int nb, std::string path);
	void setCMBZ(int CMBZ);
	void addLocation(Location location);

	// getters
	std::string getPort();
	std::string getSrvname();
	std::string getRoot();
	int getCMBZ();
	std::string getHost();
	std::map<int, std::string> getErr_page();
	std::map<int, std::string> getDefaultErrPage();
	std::vector<Location> getLocation();
	int getSd();
	Location getLocation(int index);

	// socket descriptor
	void createSd();
	void bindSd();
	void listenSd();

	// utility
	void clear();
};

#endif