#ifndef __PARSER_HPP__
#define __PARSER_HPP__
#include "inc.hpp"

class parser
{
private:
	typedef void(parser::*lvl1_fncPtr)(std::string, ServerConf&);
	typedef void(parser::*lvl2_fncPtr)(std::string, location&);
	std::string _filename, buffer;
	std::ifstream input;
	std::vector<ServerConf> servers;
	std::vector<std::string> _tokens[2];
	std::vector<parser::lvl1_fncPtr> lvl1;
	std::vector<parser::lvl2_fncPtr> lvl2;
	std::vector<std::string> _file_content;
	std::map<std::string, int> used_path;
	int serv_count;
	void _argsparser(int ac, char **av);
	void _set_token();
	void _trimString(std::string &s);
	void _rmBackSpaces(std::string &s);
	void _lookForSevOP();
	size_t _find_dash(std::string &s);
	int _count_spaces(std::string &s);
	std::string _sweep(std::string &s);
	void _token_recognizer(std::string s, int lvl, ServerConf &srv, location &l, std::string head);
	std::vector<std::string> _split(std::string s, char c);
	void _serverNameCheck(std::string s, ServerConf &srv);
	void _portCheck(std::string s, ServerConf &srv);
	void _hostCheck(std::string s, ServerConf &srv);
	void _rootCheck(std::string s, ServerConf &srv);
	void _cmbzCheck(std::string s, ServerConf &srv);
	void _errorPagesCheck(std::string s, ServerConf &srv);
	void _locationCheck(std::string s, ServerConf &srv);
	void _pathCheck(std::string s, location &l);
	void _methodsCheck(std::string s, location &l);
	void _uploadPathCheck(std::string s, location &l);
	void _rootCheck(std::string s, location &l);
	void _autoindexCheck(std::string s, location &l);
	void _indexCheck(std::string s, location &l);
	void _cgiCheck(std::string s, location &l);
	void _redirectionCheck(std::string s, location &l);
	void _returnCheck(std::string s, location &l);

public:
	parser(int ac, char **av);
	std::vector<ServerConf> _runparser();
	~parser();
};

#endif