#include "Serverconf.hpp"

ServerConf::ServerConf(std::vector<std::string> &ServContent)
{
	ServContent.erase(ServContent.begin());
	ServContent.erase(ServContent.begin());
	ServContent.erase(ServContent.end());
}
