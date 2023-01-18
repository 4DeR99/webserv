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

void ServerConf::_addErrPage(int nb, std::string s)
{
	if (!err_page[nb].empty())
		throw std::invalid_argument(DOUBLE_ERRPAGE);
	err_page[nb] = s;
}

void ServerConf::_setCMBZ(int CMBZ)
{
	if (client_max_bodt_size == -1)
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

ServerConf::~ServerConf()
{
	err_page.clear();
}
