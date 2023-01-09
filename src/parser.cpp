#include "parser.hpp"

std::vector<std::string> parser::_split(std::string &s, char c)
{
	std::string buff;
	std::stringstream str_str(s);
	std::vector<std::string> arr;
	while (getline(str_str, buff, c))
		arr.push_back(buff);
	return arr;
}

void parser::_argsparser(int ac, char **av)
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

void parser::_trimString(std::string &s)
{
	while (!s.empty() && isspace(s.front()))
		s.erase(s.begin());
	_rmBackSpaces(s);
}

void parser::_rmBackSpaces(std::string &s)
{
	while (!s.empty() && isspace(s.back()))
		s.erase(s.end());
}

void parser::_lookForSevOP()
{
	while (std::getline(input, buffer))
	{
		_rmBackSpaces(buffer);
		if (buffer.empty())
			continue;
		if (buffer == "server:")
		{
			serv_count = ONE;
			break;
		}
		else if (buffer == "servers:")
		{
			serv_count = MANY;
			break;
		}
		else if (isspace(buffer.front()))
			throw std::invalid_argument(SPACE_ERROR);
		else
			throw std::invalid_argument(TOKEN_ERROR + buffer);
	}
	_file_content.push_back(buffer);
}

int parser::_count_spaces(std::string &s)
{
	std::string::iterator it;
	it = s.begin();
	int count = 0;
	while (isspace(*it))
	{
		count++;
		if (*it == '\t')
			count++;
		it++;
	}
	return count;
}

size_t parser::_find_dash(std::string &s)
{
	std::string::iterator it;
	it = s.begin();
	while (isspace(*it))
		it++;
	if (*it == '-' && *(it + 1) == ' ')
	{
		if (*(it + 2) == ' ')
			throw std::invalid_argument(SPACE_ERROR);
		return true;
	}
	return std::string::npos;
}

// void parser::_token_recognizer(std::string &s)
// {
	
// }

void parser::_readFile()
{
	_lookForSevOP();
	int lvl = 1;
	while (std::getline(input, buffer))
	{
		std::cout << "in\n";
		_rmBackSpaces(buffer);
		buffer = buffer.substr(0, buffer.find('#'));
		if (buffer.empty())
			continue;
		// if (serv_status == NONE)
		// {
		// 	if (_find_dash(buffer) == buffer.npos)
		// 	{
		// 		if (serv_count == MANY)
		// 			throw std::invalid_argument(GEN_ERROR);
		// 		if (_count_spaces(buffer) != 2)
		// 			throw std::invalid_argument(SPACE_ERROR);
		// 		else
		// 			lvl++;
		// 	}
		// 	else
		// 	{
		// 		if (_count_spaces(buffer))
		// 			throw std::invalid_argument(SPACE_ERROR);
		// 		lvl++;
		// 	}
		// 	serv_status = ONGOING;
		// }
		// else if (serv_status == ONGOING)
		int space = _count_spaces(buffer);
		int dash = _find_dash(buffer) == buffer.npos ? 0 : 1;
		if (space == (lvl - dash - 1) * 2 && _file_content.back().back() != ':')
			lvl--;
		if (space != (lvl - dash) * 2)
			throw std::invalid_argument(SPACE_ERROR);
		if (dash && !space && !_file_content.empty())
		{
			// servers.push_back(ServerConf(_file_content));
			_file_content.clear();
		}
		// _token_recognized();
		if (buffer.back() == ':')
		 lvl++;
		_file_content.push_back(buffer);
	}
}

void parser::_runparser()
{
	_readFile();
}

parser::parser(int ac, char **av)
{
	_argsparser(ac, av);
	input.open(_filename);
	if (!input.is_open())
		throw std::invalid_argument(FILE_ERROR);
}

parser::~parser()
{
	// servers.clear();
	_file_content.clear();
}
