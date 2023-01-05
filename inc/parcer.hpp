#ifndef __PARCER_HPP__
#define __PARCER_HPP__
#include "Serverconf.hpp"

enum Serv_count
{
	ONE,
	MANY
};

enum Serv_status
{
	NONE,
	SET,
	ONGOING
};

class Parcer
{
private:
	std::string _filename, buffer;
	std::ifstream input;
	std::vector<ServerConf> servers;
	std::vector<std::string> _file_content;
	int serv_count;
	void _readFile();
	void _argsParcer(int ac, char **av);
	void _trimString(std::string &s);
	void _rmBackSpaces(std::string &s);
	void _lookForSevOP();
	void _find_
	std::vector<std::string> _split(std::string &s, char c);

public:
	Parcer(int ac, char **av);
	void _runParcer();
	~Parcer();
};

#endif