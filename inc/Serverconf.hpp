#ifndef __SERVERCONF_HPP__
#define __SERVERCONF_HPP__
#include "inc.hpp"

class ServerConf
{
private:
	std::string port;
	std::string host;
	std::string serverName;
	std::string root;
	int clientMaxBodySize;
	std::map<int, std::string> errorPage;
	std::map<int, std::string> defaultErrPage;
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
	std::vector<Location> getLocations();
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