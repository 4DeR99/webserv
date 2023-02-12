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
	lvl1.push_back(&parser::_serverNameCheck);
	_tokens[0].push_back(LVL1_PORT);
	lvl1.push_back(&parser::_portCheck);
	_tokens[0].push_back(LVL1_HOST);
	lvl1.push_back(&parser::_hostCheck);
	_tokens[0].push_back(LVL1_ROOT);
	lvl1.push_back(&parser::_rootCheck);
	_tokens[0].push_back(LVL1_CMBZ);
	lvl1.push_back(&parser::_cmbzCheck);
	_tokens[0].push_back(LVL1_ERR_PAGE);
	lvl1.push_back(&parser::_errorPagesCheck);
	_tokens[0].push_back(LVL1_LOCATION);
	lvl1.push_back(&parser::_locationCheck);
	_tokens[1].push_back(LVL2_PATH);
	lvl2.push_back(&parser::_pathCheck);
	_tokens[1].push_back(LVL2_METHODS);
	lvl2.push_back(&parser::_methodsCheck);
	_tokens[1].push_back(LVL2_ROOT);
	lvl2.push_back(&parser::_rootCheck);
	_tokens[1].push_back(LVL2_UPLOAD);
	lvl2.push_back(&parser::_uploadPathCheck);
	_tokens[1].push_back(LVL2_AUTOINDEX);
	lvl2.push_back(&parser::_autoindexCheck);
	_tokens[1].push_back(LVL2_INDEX);
	lvl2.push_back(&parser::_indexCheck);
	_tokens[1].push_back(LVL2_CGI);
	lvl2.push_back(&parser::_cgiCheck);
	_tokens[1].push_back(LVL2_REDIR);
	lvl2.push_back(&parser::_redirectionCheck);
	_tokens[1].push_back(LVL2_RETURN);
	lvl2.push_back(&parser::_returnCheck);
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

void parser::_serverNameCheck(std::string s, ServerConf &srv)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	forup(i, 0, s.size())
		if (!isprint(s[i]))
			throw std::invalid_argument(SRVNAME_ERROR);
	srv._setSrvName(s);
}

void parser::_portCheck(std::string s, ServerConf &srv)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	int port;
	try
	{
		port = std::stoi(s);
	}
	catch (const std::exception &e)
	{
		throw std::invalid_argument(PORT_ERROR);
	}
	srv._setPort(port);
}

void parser::_hostCheck(std::string s, ServerConf &srv)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	std::vector<int> r_tab(4);
	std::vector<std::string> tab;
	if (s == "localhost")
	{
		tab = _split(LOCALHOST, '.');
		forup(i, 0, 4)
		{
			r_tab[i] = std::stoi(tab[i]);
		}
		srv._setHost(r_tab);
		return;
	}
	tab = _split(s, '.');
	if (tab.size() != 4)
		throw std::invalid_argument(HOST_ERROR);
	forup(i, 0, 4)
	{
		if (tab[i].size() > 3)
			throw std::invalid_argument(HOST_ERROR);
		forup(j, 0, tab[i].size())
		{
			if (!isdigit(tab[i][j]))
				throw std::invalid_argument(HOST_ERROR);
		}
		if (std::stoi(tab[i]) < 0 || std::stoi(tab[i]) > 255)
			throw std::invalid_argument(HOST_ERROR);
		r_tab[i] = std::stoi(tab[i]);
	}
	srv._setHost(r_tab);
}

void parser::_rootCheck(std::string s, ServerConf &srv)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	if (access(s.c_str(), F_OK) == -1)
		throw std::invalid_argument(ROOT_ERROR);
	srv._setRoot(s);
}

void parser::_cmbzCheck(std::string s, ServerConf &srv)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	forup(i, 0, s.size())
		if (!isdigit(s[i]))
			throw std::invalid_argument(CMBZ_ERROR);
	int cmbz;
	try
	{
		cmbz = std::stoi(s);
	}
	catch (const std::exception &e)
	{
		throw std::invalid_argument(CMBZ_ERROR);
	}
	srv._setCMBZ(cmbz);
}

void parser::_errorPagesCheck(std::string s, ServerConf &srv)
{
	std::vector<std::string> tab = _split(s, ':');
	if (tab[0] == "error_page" && tab.size() > 1)
		throw std::invalid_argument(ERRPAGETOKEN_ERROR);
	else if (tab[0] != "error_page")
	{
		if (tab.size() != 2)
			throw std::invalid_argument(ERRPAGE_ERROR);
		_sweep(tab[1]);
		if (tab[1].front() != '/')
			throw std::invalid_argument(PATHFRNT_ERROR);
		srv._addErrPage(std::stoi(tab[0]), tab[1]);
	}
}

void parser::_locationCheck(std::string s, ServerConf &srv)
{
	std::vector<std::string> tab = _split(s, ':');
	if (tab.size() != 1)
		throw std::invalid_argument(LOCATION_ERROR);
}

void parser::_pathCheck(std::string s, location &l)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	if (s.front() != '/')
		throw std::invalid_argument(PATHFRNT_ERROR);
	if (!used_path[s])
	{
		used_path[s]++;
		l._setPath(s);
	}
	else
		throw std::invalid_argument(PATH_ERROR);
}

void parser::_methodsCheck(std::string s, location &l)
{
	std::vector<std::string> tab = _split(s, ':');
	if (tab.size() != 2)
		throw std::invalid_argument(ALMETHODS_ERROR);
	std::vector<std::string> methods = _split(tab[1], ',');
	forup(i, 0, methods.size())
	{
		_sweep(methods[i]);
		if (methods[i] != "GET" && methods[i] != "POST" && methods[i] != "DELETE")
			throw std::invalid_argument(ALMETHODS_ERROR);
	}
	forup(i, 0, methods.size())
	{
		forup(j, i + 1, methods.size())
		{
			if (methods[i] > methods[j])
			{
				std::string rep = methods[i];
				methods[i] = methods[j];
				methods[j] = rep;
				i = -1;
				break;
			}
			else if (methods[i] == methods[j])
				throw std::invalid_argument(ALMETHODS_ERROR);
		}
	}
	l._setAllowMethods(methods);
}

void parser::_uploadPathCheck(std::string s, location &l)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	forup(i, 0, s.size())
		if (isspace(s[i]))
			throw std::invalid_argument(UPLOADPATH_ERROR);
	l._setUploadPath(s);
}

void parser::_rootCheck(std::string s, location &l)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	if (access(s.c_str(), F_OK) == -1)
		throw std::invalid_argument(ROOT_ERROR);
	l._setRoot(s);
}

void parser::_autoindexCheck(std::string s, location &l)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	if (s != "on" && s != "off")
		throw std::invalid_argument(AUTOINDEX_ERROR);
	if (s == "on")
		l._setAutoIndex(true);
	else
		l._setAutoIndex(false);
}

void parser::_indexCheck(std::string s, location &l)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	forup(i, 0, s.size())
		if (isspace(s[i]))
			throw std::invalid_argument(UPLOADPATH_ERROR);
	l._setIndex(s);
}

void parser::_cgiCheck(std::string s, location &l)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	if (s.front() != '/')
		throw std::invalid_argument(CGI_ERROR);
	forup(i, 0, s.size())
		if (isspace(s[i]))
			throw std::invalid_argument(UPLOADPATH_ERROR);
	l._setCgi(s);
}

void parser::_returnCheck(std::string s, location &l)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	int r_index;
	std::vector<std::string> tab = _split(s, ' ');
	if (tab.size() != 2)
		throw std::invalid_argument(RETURN_ERROR);
	try
	{
		r_index = std::stoi(tab[0]);
	}
	catch(const std::exception& e)
	{
		throw std::invalid_argument(RETURN_ERROR);
	}
	l._setReturn(r_index, tab[1]);
}

void parser::_redirectionCheck(std::string s, location &l)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	int r_index;
	std::vector<std::string> tab = _split(s, ' ');
	if (tab.size() != 2)
		throw std::invalid_argument(RETURN_ERROR);
	try
	{
		r_index = std::stoi(tab[0]);
		l._setRedirection(r_index, tab[1]);
	}
	catch(const std::exception& e)
	{
		throw std::invalid_argument(RETURN_ERROR);
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

void parser::_token_recognizer(std::string s, int lvl, ServerConf &srv, location &l, std::string head)
{
	if (head == "server" || head == "location")
	{
		std::vector<std::string>::iterator it = _tokens[lvl].end();
		it = std::find(_tokens[lvl].begin(), _tokens[lvl].end(), s.substr(0, s.find(':')));
		if (it == _tokens[lvl].end())
			throw std::invalid_argument(TOKEN_ERROR + s);
		else if (!lvl)
			(this->*lvl1[it - _tokens[lvl].begin()])(s, srv);
		else
			(this->*lvl2[it - _tokens[lvl].begin()])(s, l);
	}
	else if (head == "error_page")
	{
		int err_nb;
		try
		{
			err_nb = std::stoi(s.substr(0, s.find(':')));
		}
		catch (const std::exception &e)
		{
			throw std::invalid_argument(TOKEN_ERROR + s);
		}
		_errorPagesCheck(s, srv);
	}
	else
		throw std::invalid_argument(GEN_ERROR);
}

std::string parser::_sweep(std::string &s)
{
	_trimString(s);
	if (s.front() == '-')
	{
		s.erase(s.begin());
		s.erase(s.begin());
	}
	return s;
}

std::vector<ServerConf> parser::_runparser()
{
	ServerConf srv;
	location l;
	std::string head = "server";
	std::string old_head;
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
		int space = _count_spaces(buffer);
		int dash = _find_dash(buffer) == buffer.npos ? 0 : 1;
		if (space == (lvl - dash - 1) * 2 && _file_content.back().back() != ':')
		{
			lvl--;
			head = old_head;
		}
		if (space != (lvl - dash) * 2)
			throw std::invalid_argument(SPACE_ERROR + buffer);
		if (dash && !space && !_file_content.empty())
		{
			servers.push_back(srv);
			srv.clear();
			_file_content.clear();
			used_path.clear();
		}
		if (dash && space == 2 && !l.empty())
		{
			srv._addLocation(l);
			l.clear();
		}
		_sweep(buffer);
		_token_recognizer(buffer, lvl - 1, srv, l, head);
		if (buffer.back() == ':')
		{
			lvl++;
			old_head = head;
			head = buffer.substr(0, buffer.find(':'));
		}
		if (lvl > 2)
			throw std::invalid_argument(GEN_ERROR);
		_file_content.push_back(buffer);
	}
	return servers;
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
