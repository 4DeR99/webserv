#include "inc.hpp"

int main(int ac, char **av)
{
	try
	{
		parser webhamid(ac, av);
		std::vector<ServerConf> servers = webhamid._runparser();
		Pollge pollin;
		forup(i, 0, servers.size()){
			servers[i].createSd();
			servers[i].bindSd();
			servers[i].listenSd();
			pollin._addSd(servers[i]._getSd(), i);
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}