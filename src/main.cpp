#include "parser.hpp"

int main(int ac, char **av)
{
	try
	{
		parser webhamid(ac, av);
		std::vector<ServerConf> servers = webhamid._runparser();
		std::cout << servers.size() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}