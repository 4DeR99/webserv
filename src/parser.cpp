#include "parser.hpp"

std::vector<std::string> parser::_split(std::string s, char c)
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

void parser::_set_token()
{
	_tokens[0].push_back(LVL1_SRV_NAME);
	_tokens[0].push_back(LVL1_PORT);
	_tokens[0].push_back(LVL1_HOST);
	_tokens[0].push_back(LVL1_ROOT);
	_tokens[0].push_back(LVL1_CMBZ);
	_tokens[0].push_back(LVL1_ERR_PAGE);
	_tokens[0].push_back(LVL1_LOCATION);
	_tokens[1].push_back(LVL2_PATH);
	_tokens[1].push_back(LVL2_METHODS);
	_tokens[1].push_back(LVL2_ROOT);
	_tokens[1].push_back(LVL2_UPLOAD);
	_tokens[1].push_back(LVL2_AUTOINDEX);
	_tokens[1].push_back(LVL2_INDEX);
	_tokens[1].push_back(LVL2_CGI);
	_tokens[1].push_back(LVL2_REDIR);
	_tokens[1].push_back(LVL2_RETURN);
	_tokens[1].push_back(LVL2_3_RNDM_N);
	_tokens[2].push_back(LVL2_3_RNDM_N);
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
		s.erase(s.end() - 1);
}

void parser::_lookForSevOP()
{
	while (std::getline(input, buffer))
	{
		if (buffer.find('\t') != buffer.npos)
			throw std::invalid_argument(TAB_ERROR);
		_rmBackSpaces(buffer);
		buffer = buffer.substr(0, buffer.find('#'));
		if (buffer.empty())
			continue;
		if (buffer == "server:")
			break;
		else if (isspace(buffer.front()))
			throw std::invalid_argument(SPACE_ERROR + buffer);
		else
			throw std::invalid_argument(TOKEN_ERROR + buffer);
	}
	_file_content.push_back(buffer);
}

std::string parser::_serverNameCheck(std::string s)
{
	std::string::iterator it = std::find(s.begin(), s.end(), ":");
	std::string::iterator beg;
	while (it != s.end() && isspace(*it))
		it++;
	beg = it;
	while (it != s.end())
	{
		if (!isprint(*it))
			throw std::invalid_argument(SRVNAME_ERROR);
		it++;
	}
	return std::string(beg, it);
}

int parser::_portCheck(std::string s)
{
	std::string::iterator it = std::find(s.begin(), s.end(), ":");
	while (it != s.end() && isspace(*it))
		it++;
	std::string sub(it, s.end());
	try
	{
		return stoi(sub);
	}
	catch (const std::exception &e)
	{
		throw std::invalid_argument(PORT_ERROR);
	}
}

std::vector<int> parser::_hostCheck(std::string s)
{
	std::string::iterator beg = std::find(s.begin(), s.end(), ":");
	std::vector<int> r_tab(4);
	std::vector<std::string> tab;
	while (beg != s.end() && isspace(*beg))
		beg++;
	if (std::string(beg, s.end()) == "localhost")
	{
		tab = _split(LOCALHOST, '.');
		forup(i, 0, 4)
		{
			r_tab[i] = std::stoi(tab[i]);
		}
		return r_tab;
	}
	tab = _split(std::string(beg, s.end()), '.');
	if (tab.size() != 4)
		throw std::invalid_argument(HOST_ERROR);
	forup(i, 0, 4)
	{
		if (tab[i].size() > 3)
			throw std::invalid_argument(HOST_ERROR);
		forup(j, 0, 3)
		{
			if (!isdigit(tab[i][j]))
				throw std::invalid_argument(HOST_ERROR);
		}
		if (std::stoi(tab[i]) < 0 || std::stoi(tab[i]) > 255)
			throw std::invalid_argument(HOST_ERROR);
		r_tab[i] = std::stoi(tab[i]);
	}
	return r_tab;
}

std::string parser::_rootCheck(std::string s)
{
	std::string::iterator it = std::find(s.begin(), s.end(), ":");
	while (it != s.end() && isspace(*it))
		it++;
	std::fstream root(std::string(it, s.end()));
	if (!root.is_open())
		throw std::invalid_argument(ROOT_ERROR);
	return std::string(it, s.end());
}

int parser::_cmbzCheck(std::string s)
{
	std::string::iterator it = std::find(s.begin(), s.end(), ":");
	while (it != s.end() && isspace(*it))
		it++;
	for (std::string::iterator i = it; i != s.end(); i++)
	{
		if (!isdigit(*i))
			throw std::invalid_argument(CMBZ_ERROR);
	}
	try
	{
		return std::stoi(std::string(it, s.end()));
	}
	catch (const std::exception &e)
	{
		throw std::invalid_argument(CMBZ_ERROR);
	}
}



int parser::_count_spaces(std::string &s)
{
	std::string::iterator it;
	it = s.begin();
	int count = 0;
	while (isspace(*it))
	{
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
			throw std::invalid_argument(SPACE_ERROR + s);
		return true;
	}
	return std::string::npos;
}

void parser::_token_recognizer(std::string s, int lvl, ServerConf srv)
{
	int rndm_nb;
	std::vector<std::string>::iterator it = _tokens[lvl].end();

	it = std::find(_tokens[lvl].begin(), _tokens[lvl].end(), s.substr(0, s.find(':')));
	if (lvl && it == _tokens[lvl].end())
	{
		try
		{
			rndm_nb = stoi(s.substr(0, s.find(':')));
			it = std::find(_tokens[lvl].begin(), _tokens[lvl].end(), LVL2_3_RNDM_N);
		}
		catch (std::exception &e)
		{
			it = _tokens[lvl].end();
		}
	}
	if (it == _tokens[lvl].end())
		throw std::invalid_argument(TOKEN_ERROR + s);
	// if ()
}

std::string parser::_sweep(std::string s)
{
	_trimString(s);
	if (s.front() == '-')
	{
		s.erase(s.begin());
		s.erase(s.begin());
	}
	return s;
}

void parser::_readFile()
{
	ServerConf srv;
	_lookForSevOP();
	int lvl = 1;
	while (std::getline(input, buffer))
	{
		if (buffer.find('\t') != buffer.npos)
			throw std::invalid_argument(TAB_ERROR);
		_rmBackSpaces(buffer);
		buffer = buffer.substr(0, buffer.find('#'));
		if (buffer.empty())
			continue;
		std::cout << buffer << std::endl;
		int space = _count_spaces(buffer);
		int dash = _find_dash(buffer) == buffer.npos ? 0 : 1;
		if (space == (lvl - dash - 1) * 2 && _file_content.back().back() != ':')
			lvl--;
		else if (space == (lvl - dash - 2) * 2 && _file_content.back().back() != ':')
			lvl -= 2;
		if (space != (lvl - dash) * 2)
			throw std::invalid_argument(SPACE_ERROR + buffer);
		if (dash && !space && !_file_content.empty())
		{
			// servers.push_back(ServerConf(_file_content));
			_file_content.clear();
		}
		_token_recognizer(_sweep(buffer), lvl - 1, srv);
		if (buffer.back() == ':')
			lvl++;
		if (lvl > 3)
			throw std::invalid_argument(GEN_ERROR);
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
	_set_token();
}

parser::~parser()
{
	// servers.clear();
	_file_content.clear();
}
