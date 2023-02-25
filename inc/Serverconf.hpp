#ifndef __SERVERCONF_HPP__
#define __SERVERCONF_HPP__
#include "inc.hpp"

class ServerConf
{
private:
	int sd, on;
	std::string port, host, server_name, root;
	int client_max_body_size;
	std::map<int, std::string> err_page, defaultErrPage;
	std::vector<location> loc;
	std::map<std::string, int> l_path;
	struct addrinfo hints, *res;

public:
	ServerConf();
	ServerConf(ServerConf const &_2Copy);
	ServerConf &operator=(ServerConf const &_2Copy);
	~ServerConf();

	// setters
	void setPort(std::string n);
	void setSrvName(std::string s);
	void setRoot(std::string s);
	void setHost(std::string s);
	void addErrPage(int nb, std::string s);
	void setCMBZ(int CMBZ);
	void addLocation(location l);

	// getters
	std::string getPort();
	std::string getSrvname();
	std::string getRoot();
	int getCMBZ();
	std::string getHost();
	std::map<int, std::string> getErr_page();
	std::map<int, std::string> getDefaultErrPage();
	std::vector<location> getLocation();
	int getSd();
	location getLocationByUrl(std::string &url); // to do

	// socket descriptor
	void createSd();
	void bindSd();
	void listenSd();

	// utility
	void clear();
};

#endif