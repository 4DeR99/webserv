#include "parcer.hpp"

std::vector<std::string> Parcer::_split(std::string &s, char c)
{
	std::string buff;
	std::stringstream str_str(s);
	std::vector<std::string> arr;
	while (getline(str_str, buff, c))
		arr.push_back(buff);
	return arr;
}

void Parcer::_argsParcer(int ac, char **av)
{
	if (ac != 2 || av == NULL)
		throw std::invalid_argument("Invalid arguments!\n try: ./Webserv + ConfigFile.conf");
	else if (ac == 1)
		_filename = "./ConfigFile.conf";
	else
		_filename = av[1];
	std::vector<std::string> arr = _split(_filename, '.');
	if (arr.back() != "conf")
		throw std::invalid_argument(EXTENTION_ERROE);
}

void Parcer::_trimString(std::string &s)
{
	while (!s.empty() && isspace(s.front()))
		s.erase(s.begin());
	_rmBackSpaces(s);
}

void Parcer::_rmBackSpaces(std::string &s)
{
	while (!s.empty() && isspace(s.back()))
		s.erase(s.end());
}

void Parcer::_lookForSevOP()
{
	while (std::getline(input, buffer)){
		_rmBackSpaces(buffer);
		if (buffer.empty())
			continue;
		if (buffer == "server:")
			serv_count = ONE;
		else if (buffer == "servers:")
			serv_count = MANY;
		else if (isspace(buffer.front()))
			throw std::invalid_argument(SPACE_ERROR);
		else
			throw std::invalid_argument(TOKEN_ERROR + buffer);
	}
}

void Parcer::_readFile()
{
	int serv_status = NONE;
	int LVL = 0;
	_lookForSevOP();
	while (std::getline(input, buffer))
	{
		_rmBackSpaces(buffer);
		if (buffer.empty())
			continue;
		if ()
	}
}

void Parcer::_runParcer()
{
	_readFile();
}

Parcer::Parcer(int ac, char **av)
{
	_argsParcer(ac, av);
	input.open(_filename);
	if (!input.is_open())
		throw std::invalid_argument(FILE_ERROR);
}

Parcer::~Parcer()
{
	servers.clear();
	_file_content.clear();
}
