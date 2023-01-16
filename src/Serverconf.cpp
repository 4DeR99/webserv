#include "Serverconf.hpp"

ServerConf::ServerConf() : port(-1), client_max_bodt_size(-1)
{
}

void ServerConf::_setPort(int n)
{
	if (n != -1)
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

ServerConf::~ServerConf()
{
	err_page.clear();
}
