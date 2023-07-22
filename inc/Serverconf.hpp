#ifndef __SERVERCONF_HPP__
#define __SERVERCONF_HPP__
#include "Inc.hpp"

class ServerConf
{
private:
	std::vector<std::string> port;
	std::map<std::string, int> portMap;
	std::string host;
	std::string root;
	std::string serverName;
	int clientMaxBodySize;
	int send_buffer_size;
	std::vector<Location> locations;
	std::map<int, std::string> errorPage;
	std::map<std::string, int> locationsPath;

	std::vector<int> sd;
	int on;
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
	void setSendBufferSize(int sendBufferSize);
	void setSd(int sd);

	// getters
	std::vector<std::string> getPort();
	std::string getSrvname();
	std::string getRoot();
	int getCMBZ();
	std::string getHost();
	std::map<int, std::string> getErr_page();
	std::vector<Location>& getLocations();
	int getSd(int index);
	std::vector<int> getSds();
	Location getLocation(int index);
	int getSendBufferSize();

	// socket descriptor
	void createSd(int index);
	void bindSd(int index);
	void listenSd(int index);

	// utility
	void clear();
};

#endif