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
			forup(j, 0, servers[i].getPort().size())
			{
				servers[i].createSd(j);
				servers[i].bindSd(j);
				servers[i].listenSd(j);
				pollin._addSd(servers[i].getSd(j), i + 1, servers[i].getSendBufferSize());
			}
		}
		pollin._run();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}