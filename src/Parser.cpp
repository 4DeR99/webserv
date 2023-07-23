#include "Inc.hpp"

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
	// _tokens[1].push_back(LVL2_REDIR);
	// lvl2.push_back(&parser::_redirectionCheck);
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
			throw std::invalid_argument(TOKEN_ERROR + buffer + ".");
	}
}

void parser::_serverNameCheck(std::string s, ServerConf &srv)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	forup(i, 0, s.size()) if (!isprint(s[i])) throw std::invalid_argument(SRVNAME_ERROR);
	srv.setSrvName(s);
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
	srv.setPort(s);
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
		srv.setHost(s);
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
	srv.setHost(s);
}

void parser::_rootCheck(std::string s, ServerConf &srv)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	if (access(s.c_str(), F_OK) == -1)
		throw std::invalid_argument(ROOT_ERROR);
	srv.setRoot(s);
}

void parser::_cmbzCheck(std::string s, ServerConf &srv)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	forup(i, 0, s.size()) if (!isdigit(s[i])) throw std::invalid_argument(CMBZ_ERROR);
	int cmbz;
	try
	{
		cmbz = std::stoi(s);
	}
	catch (const std::exception &e)
	{
		throw std::invalid_argument(CMBZ_ERROR);
	}
	srv.setCMBZ(cmbz);
}

void parser::_errorPagesCheck(std::string s, ServerConf &srv)
{
	std::vector<std::string> tab = _split(s, ':');
	if (tab[0] == "error_page" && tab.size() > 1)
		throw std::invalid_argument(ERRPAGETOKEN_ERROR);
	else if (tab[0] != "error_page")
	{
		if (tab.size() != 2)
			throw std::invalid_argument(ERRPAGE_ERROR + s);
		_sweep(tab[1]);
		if (access(tab[1].c_str(), F_OK) == -1)
			throw std::invalid_argument(ERRPAGE_ERROR + s);
		srv.addErrPage(std::stoi(tab[0]), tab[1]);
	}
}

void parser::_locationCheck(std::string s, ServerConf &srv)
{
	_sweep(s);
	(void)srv;
	std::vector<std::string> tab = _split(s, ':');
	if (tab.size() != 1 || s.back() != ':')
		throw std::invalid_argument(LOCATION_ERROR);
}

void parser::_pathCheck(std::string s, Location &location)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	if (s.front() != '/')
		throw std::invalid_argument(PATHFRNT_ERROR);
	if (!used_path[s])
	{
		used_path[s]++;
		location.setPath(s);
	}
	else
		throw std::invalid_argument(PATH_ERROR);
}

void parser::_methodsCheck(std::string s, Location &location)
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
	location.setAllowMethods(methods);
}

void parser::_uploadPathCheck(std::string s, Location &location)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	forup(i, 0, s.size()) if (isspace(s[i])) throw std::invalid_argument(UPLOADPATH_ERROR);
	if (access(s.c_str(), F_OK) == -1)
		throw std::invalid_argument(UPLOADPATH_ERROR);
	location.setUploadPath(s);
}

void parser::_rootCheck(std::string s, Location &location)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	if (access(s.c_str(), F_OK) == -1)
		throw std::invalid_argument(ROOT_ERROR);
	location.setRoot(s);
}

void parser::_autoindexCheck(std::string s, Location &location)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	if (s != "on" && s != "off")
		throw std::invalid_argument(AUTOINDEX_ERROR);
	if (s == "on")
		location.setAutoIndex(true);
	else
		location.setAutoIndex(false);
}

void parser::_indexCheck(std::string s, Location &location)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	forup(i, 0, s.size()) if (isspace(s[i])) throw std::invalid_argument(INDEX_ERROR);
	location.setIndex(s);
}

void parser::_cgiCheck(std::string s, Location &location)
{
	s = std::string(std::find(s.begin(), s.end(), ':') + 1, s.end());
	_sweep(s);
	forup(i, 0, s.size()) if (isspace(s[i])) throw std::invalid_argument(CGI_ERROR);
	if (access(s.c_str(), F_OK) == -1)
		throw std::invalid_argument(CGI_ERROR);
	location.setCgi(s);
}

void parser::_returnCheck(std::string s, Location &location)
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
		if (r_index != 301)
			throw std::invalid_argument(RETURN_ERROR);
	}
	catch (const std::exception &e)
	{
		throw std::invalid_argument(RETURN_ERROR);
	}
	location.setReturn(r_index, tab[1]);
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

void parser::_token_recognizer(std::string s, int lvl, ServerConf &srv, Location &location, std::string head)
{
	if (head == "server" || head == "location")
	{
		std::vector<std::string>::iterator it = _tokens[lvl].end();
		it = std::find(_tokens[lvl].begin(), _tokens[lvl].end(), s.substr(0, s.find(':')));
		if (it == _tokens[lvl].end())
			throw std::invalid_argument(TOKEN_ERROR + s + ".");
		else if (!lvl)
			(this->*lvl1[it - _tokens[lvl].begin()])(s, srv);
		else
			(this->*lvl2[it - _tokens[lvl].begin()])(s, location);
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
			throw std::invalid_argument(TOKEN_ERROR + s + ".");
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

std::string parser::_cleanse(std::string &s)
{
	std::string copy = s;
	_trimString(copy);
	while (copy.front() == '/')
		copy.erase(copy.begin());
	while (copy.back() == '/')
		copy.erase(copy.end() - 1);
	return copy;
}

void parser::_setDefaultLocationsDetails()
{
	forup(i, 0, servers.size())
	{
		if (servers[i].getPort().empty())
			throw std::invalid_argument(PORT_MISSING);
		if (servers[i].getRoot().empty())
			throw std::invalid_argument(ROOT_MISSING);
		forup(j, 0, servers[i].getLocations().size())
		{
			Location &location = servers[i].getLocations()[j];
			if (!location.getReturnPath().empty() && _cleanse(location.getReturnPath()) == _cleanse(location.getPath()))
				throw std::invalid_argument(REDIR_ERROR);
			if (location.getPath().empty())
				throw std::invalid_argument(PATH_MISSING);
			if (location.getMethods().empty())
				location.getMethods().push_back("GET");
			if (location.getRoot().empty())
				location.setRoot(servers[i].getRoot());
		}
	}
}

bool parser::_isAllSpace(std::string &s)
{
	forup(i, 0, s.size())
	{
		if (!isspace(s[i]))
			return false;
	}
	return true;
}

std::vector<ServerConf> parser::_runparser()
{
	ServerConf srv;
	Location location;
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
		if (buffer.empty() || _isAllSpace(buffer))
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
			srv.addLocation(location);
			servers.push_back(ServerConf(srv));
			location.clear();
			srv.clear();
			_file_content.clear();
			used_path.clear();
		}
		if (dash && space == 2 && !location.empty())
		{
			srv.addLocation(location);
			location.clear();
		}
		_sweep(buffer);
		_token_recognizer(buffer, lvl - 1, srv, location, head);
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
	if (!location.empty())
		srv.addLocation(location);
	servers.push_back(ServerConf(srv));
	_setDefaultLocationsDetails();
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
	servers.clear();
	_file_content.clear();
}
