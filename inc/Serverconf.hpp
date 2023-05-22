#ifndef __SERVERCONF_HPP__
#define __SERVERCONF_HPP__
#include "Inc.hpp"

class ServerConf
{
private:
	std::string port;
	std::string host;
	std::string root;
	std::string serverName;
	int clientMaxBodySize;
	int send_buffer_size;
	std::vector<Location> locations;
	std::map<int, std::string> errorPage;
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
	void setSendBufferSize(int sendBufferSize);
	void setSd(int sd);

	// getters
	std::string getPort();
	std::string getSrvname();
	std::string getRoot();
	int getCMBZ();
	std::string getHost();
	std::map<int, std::string> getErr_page();
	std::vector<Location>& getLocations();
	int getSd();
	Location getLocation(int index);
	int getSendBufferSize();

	// socket descriptor
	void createSd();
	void bindSd();
	void listenSd();

	// utility
	void clear();
};

#endif