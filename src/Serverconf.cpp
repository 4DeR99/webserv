#include "inc.hpp"

ServerConf::ServerConf() : client_max_bodt_size(-1)
{
}

void ServerConf::_setPort(std::string n)
{
	if (!port.empty())
		throw std::invalid_argument(DOUBLE_PORT);
	port = n;
}

void ServerConf::_setHost(std::string s)
{
	if (!host.empty())
		throw std::invalid_argument(DOUBLE_HOST);
	host = s;
}

void ServerConf::_setRoot(std::string s)
{
	if (!root.empty())
		throw std::invalid_argument(DOUBLE_ROOT);
	root = s;
}

void ServerConf::_setSrvName(std::string s)
{
	if (!server_name.empty())
		throw std::invalid_argument(DOUBLE_SRVNAME);
	server_name = s;
}

void ServerConf::_addErrPage(int nb, std::string s)
{
	if (!err_page[nb].empty())
		throw std::invalid_argument(DOUBLE_ERRPAGE);
	err_page[nb] = s;
}

void ServerConf::_setCMBZ(int CMBZ)
{
	if (client_max_bodt_size != -1)
		throw std::invalid_argument(DOUBLE_CMBZ);
	client_max_bodt_size = CMBZ;
}

void ServerConf::_addLocation(location l)
{
	if (l_path[l._getPath()])
		throw std::invalid_argument(DOUBLE_LOCATION_PATH);
	loc.push_back(l);
	l_path[l._getPath()]++;
}

std::string ServerConf::_getPort()
{
	return port;
}

std::string ServerConf::_getSrvname()
{
	return server_name;
}

std::string ServerConf::_getRoot()
{
	return root;
}

int ServerConf::_getCMBZ()
{
	return client_max_bodt_size;
}

std::string ServerConf::_getHost()
{
	return host;
}

std::map<int, std::string> ServerConf::_getErr_page()
{
	return err_page;
}

std::vector<location> ServerConf::_getLocation()
{
	return loc;
}

int ServerConf::_getSd()
{
	return sd;
}

void ServerConf::createSd()
{
	int rc;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	rc = getaddrinfo(this->_getHost().c_str(), this->_getPort().c_str(), &hints, &res) != 0;
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
	if (rc < 0){
		close(this->sd);
		throw std::runtime_error("listen() failed");
	}
}

void ServerConf::clear(){
	port = -1;
	server_name.clear();
	root.clear();
	client_max_bodt_size = -1;
	host.clear();
	err_page.clear();
	loc.clear();
	l_path.clear();
}

ServerConf::~ServerConf()
{
	err_page.clear();
}
