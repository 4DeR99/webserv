#include "Inc.hpp"

int main(int ac, char **av)
{
	try
	{
		parser webhamid(ac, av);
		std::vector<ServerConf> servers = webhamid._runparser();
		Pollge pollin(servers);
		forup(i, 0, servers.size())
		{
			servers[i].createSd();
			servers[i].bindSd();
			servers[i].listenSd();
			pollin._addSd(servers[i].getSd(), i + 1);
		}
		pollin._run();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}