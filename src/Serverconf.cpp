#include "Inc.hpp"

ServerConf::ServerConf()
		: clientMaxBodySize(-1),
			sd(-1)
{
}

ServerConf::ServerConf(ServerConf const &_2Copy)
{
	this->operator=(_2Copy);
}

ServerConf &ServerConf::operator=(ServerConf const &_2Copy)
{
	this->sd = _2Copy.sd;
	this->on = _2Copy.on;
	this->port = _2Copy.port;
	this->host = _2Copy.host;
	this->serverName = _2Copy.serverName;
	this->root = _2Copy.root;
	this->clientMaxBodySize = _2Copy.clientMaxBodySize;
	this->errorPage = _2Copy.errorPage;
	this->locations = _2Copy.locations;
	this->locationsPath = _2Copy.locationsPath;
	return *this;
}

void ServerConf::setPort(std::string port)
{
	if (!this->port.empty())
		throw std::invalid_argument(DOUBLE_PORT);
	this->port = port;
}

void ServerConf::setHost(std::string host)
{
	if (!this->host.empty())
		throw std::invalid_argument(DOUBLE_HOST);
	this->host = host;
}

void ServerConf::setRoot(std::string root)
{
	if (!this->root.empty())
		throw std::invalid_argument(DOUBLE_ROOT);
	this->root = root;
}

void ServerConf::setSrvName(std::string srvname)
{
	if (!this->serverName.empty())
		throw std::invalid_argument(DOUBLE_SRVNAME);
	this->serverName = srvname;
}

void ServerConf::addErrPage(int nb, std::string path)
{
	if (!this->errorPage[nb].empty())
		throw std::invalid_argument(DOUBLE_ERRPAGE);
	errorPage[nb] = path;
}

void ServerConf::setCMBZ(int CMBZ)
{
	if (this->clientMaxBodySize != -1)
		throw std::invalid_argument(DOUBLE_CMBZ);
	clientMaxBodySize = CMBZ;
}

void ServerConf::addLocation(Location location)
{
	if (this->locationsPath[location.getPath()])
		throw std::invalid_argument(DOUBLE_LOCATION_PATH);
	locations.push_back(location);
	locationsPath[location.getPath()]++;
}

Location ServerConf::getLocation(int index)
{
	if (index < 0 || index >= (int)locations.size())
		throw std::invalid_argument("Ivalid index");
	return locations[index];
}

void ServerConf::createSd()
{
	int rc;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	rc = getaddrinfo(this->getHost().c_str(), this->getPort().c_str(), &hints, &res) != 0;
	if (rc != 0)
		throw std::runtime_error("getaddrinfo() failed");
	// CREATING A IPV4 SOCKET
	this->sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (this->sd < 0)
	{
		throw std::runtime_error("socket() failed");
		exit(-1);
	}
	// ALLOWING SD TO BE REUSABLE
	rc = setsockopt(this->sd, SOL_SOCKET, SO_REUSEADDR,
									(char *)&this->on, sizeof(this->on));
	if (rc < 0)
	{
		close(this->sd);
		throw std::runtime_error("setsockopt() failed");
	}
	// SET SD TO BE NONBLOCKING
	rc = fcntl(this->sd, F_SETFL, O_NONBLOCK);
	if (rc < 0)
	{
		close(this->sd);
		throw std::runtime_error("fcntl() failed");
	}
}

void ServerConf::bindSd()
{
	int rc;

	rc = ::bind(this->sd, this->res->ai_addr, this->res->ai_addrlen);
	if (rc < 0)
	{
		close(this->sd);
		throw std::runtime_error("bind() failed");
	}
}

void ServerConf::listenSd()
{
	int rc;

	rc = listen(this->sd, 100);
	if (rc < 0)
	{
		close(this->sd);
		throw std::runtime_error("listen() failed");
	}
}

std::string ServerConf::getPort() { return port; }

std::string ServerConf::getSrvname() { return serverName; }

std::string ServerConf::getRoot() { return root; }

int ServerConf::getCMBZ() { return clientMaxBodySize; }

std::string ServerConf::getHost() { return host; }

std::map<int, std::string> ServerConf::getErr_page() { return errorPage; }

std::vector<Location> ServerConf::getLocations() { return locations; }

int ServerConf::getSd() { return sd; }

void ServerConf::clear()
{
	port.clear();
	serverName.clear();
	root.clear();
	clientMaxBodySize = -1;
	host.clear();
	errorPage.clear();
	locations.clear();
	locationsPath.clear();
}

ServerConf::~ServerConf()
{
	errorPage.clear();
}
