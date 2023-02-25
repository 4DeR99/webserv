#include "inc.hpp"

ServerConf::ServerConf()
		: client_max_body_size(-1),
			sd(-1)
{
	defaultErrPage[400] = "./defaultErrorPages/400.html";
	defaultErrPage[401] = "./defaultErrorPages/401.html";
	defaultErrPage[404] = "./defaultErrorPages/404.html";
	defaultErrPage[500] = "./defaultErrorPages/500.html";
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
	this->server_name = _2Copy.server_name;
	this->root = _2Copy.root;
	this->client_max_body_size = _2Copy.client_max_body_size;
	this->err_page = _2Copy.err_page;
	this->loc = _2Copy.loc;
	this->l_path = _2Copy.l_path;
	return *this;
}

void ServerConf::setPort(std::string n)
{
	if (!port.empty())
		throw std::invalid_argument(DOUBLE_PORT);
	port = n;
}

void ServerConf::setHost(std::string s)
{
	if (!host.empty())
		throw std::invalid_argument(DOUBLE_HOST);
	host = s;
}

void ServerConf::setRoot(std::string s)
{
	if (!root.empty())
		throw std::invalid_argument(DOUBLE_ROOT);
	root = s;
}

void ServerConf::setSrvName(std::string s)
{
	if (!server_name.empty())
		throw std::invalid_argument(DOUBLE_SRVNAME);
	server_name = s;
}

void ServerConf::addErrPage(int nb, std::string s)
{
	if (!err_page[nb].empty())
		throw std::invalid_argument(DOUBLE_ERRPAGE);
	err_page[nb] = s;
}

void ServerConf::setCMBZ(int CMBZ)
{
	if (client_max_body_size != -1)
		throw std::invalid_argument(DOUBLE_CMBZ);
	client_max_body_size = CMBZ;
}

void ServerConf::addLocation(location l)
{
	if (l_path[l._getPath()])
		throw std::invalid_argument(DOUBLE_LOCATION_PATH);
	loc.push_back(l);
	l_path[l._getPath()]++;
}

std::string ServerConf::getPort()
{
	return port;
}

std::string ServerConf::getSrvname()
{
	return server_name;
}

std::string ServerConf::getRoot()
{
	return root;
}

int ServerConf::getCMBZ()
{
	return client_max_body_size;
}

std::string ServerConf::getHost()
{
	return host;
}

std::map<int, std::string> ServerConf::getErr_page()
{
	return err_page;
}

std::map<int, std::string> ServerConf::getDefaultErrPage()
{
	return defaultErrPage;
}

std::vector<location> ServerConf::getLocation()
{
	return loc;
}

int ServerConf::getSd()
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

void ServerConf::clear()
{
	port.clear();
	server_name.clear();
	root.clear();
	client_max_body_size = -1;
	host.clear();
	err_page.clear();
	loc.clear();
	l_path.clear();
}

ServerConf::~ServerConf()
{
	err_page.clear();
}
