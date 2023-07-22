#include "Inc.hpp"

ServerConf::ServerConf()
		: clientMaxBodySize(-1),
			send_buffer_size(0)
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
	this->send_buffer_size = _2Copy.send_buffer_size;
	return *this;
}

void ServerConf::setPort(std::string port)
{
	if (this->portMap[port] > 0)
		throw std::invalid_argument(DUPPED_PORT);
	this->port.push_back(port);
	this->portMap[port]++;
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

void ServerConf::setSendBufferSize(int size) { this->send_buffer_size = size; }

void ServerConf::setSd(int sd) { this->sd.push_back(sd); }

void ServerConf::createSd(int index)
{
	int rc, tmp_sd;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	rc = getaddrinfo(this->getHost().c_str(), this->getPort()[index].c_str(), &hints, &res) != 0;
	if (rc != 0)
		throw std::runtime_error("getaddrinfo() failed");
	// CREATING A IPV4 SOCKET
	tmp_sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (tmp_sd < 0)
	{
		throw std::runtime_error("socket() failed");
		exit(-1);
	}
	// ALLOWING SD TO BE REUSABLE
	rc = setsockopt(tmp_sd, SOL_SOCKET, SO_REUSEADDR,
									(char *)&this->on, sizeof(this->on));
	if (rc < 0)
	{
		close(tmp_sd);
		throw std::runtime_error("setsockopt() failed");
	}
	// SET SD TO BE NONBLOCKING
	rc = fcntl(tmp_sd, F_SETFL, O_NONBLOCK);
	if (rc < 0)
	{
		close(tmp_sd);
		throw std::runtime_error("fcntl() failed");
	}
	// GETTING THE SIZE OF THE SEND BUFFER
	socklen_t optlen = sizeof(this->send_buffer_size);
	int result = getsockopt(tmp_sd, SOL_SOCKET, SO_SNDBUF, &this->send_buffer_size, &optlen);
	this->send_buffer_size /= 2;
	if (result == -1)
	{
		close(tmp_sd);
		throw std::runtime_error("getsockopt() failed");
	}
	this->sd.push_back(tmp_sd);
}

void ServerConf::bindSd(int index)
{
	int rc;

	rc = ::bind(this->sd[index], this->res->ai_addr, this->res->ai_addrlen);
	if (rc < 0)
	{
		close(this->sd[index]);
		throw std::runtime_error("bind() failed");
	}
}

void ServerConf::listenSd(int index)
{
	int rc;

	rc = listen(this->sd[index], 100);
	if (rc < 0)
	{
		close(this->sd[index]);
		throw std::runtime_error("listen() failed");
	}
}

std::vector<std::string> ServerConf::getPort() { return port; }

std::string ServerConf::getSrvname() { return serverName; }

std::string ServerConf::getRoot() { return root; }

int ServerConf::getCMBZ() { return clientMaxBodySize; }

std::string ServerConf::getHost() { return host; }

std::map<int, std::string> ServerConf::getErr_page() { return errorPage; }

std::vector<Location>& ServerConf::getLocations() { return locations; }

int ServerConf::getSendBufferSize() { return this->send_buffer_size; }

int ServerConf::getSd(int index) { return sd[index]; }

std::vector<int> ServerConf::getSds() { return sd; }

void ServerConf::clear()
{
	port.clear();
	portMap.clear();
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
