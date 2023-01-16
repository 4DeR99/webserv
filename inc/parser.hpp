#ifndef __PARSER_HPP__
#define __PARSER_HPP__
#include "Serverconf.hpp"

enum Serv_count
{
	ONE,
	MANY
};

class parser
{
private:
	std::string _filename, buffer;
	std::ifstream input;
	// std::vector<ServerConf> servers;
	std::vector<std::string> _tokens[3];
	std::vector<std::string> _file_content;
	int serv_count;
	void _readFile();
	void _argsparser(int ac, char **av);
	void _set_token();
	void _trimString(std::string &s);
	void _rmBackSpaces(std::string &s);
	void _lookForSevOP();
	size_t _find_dash(std::string &s);
	int _count_spaces(std::string &s);
	std::string _sweep(std::string s);
	void _token_recognizer(std::string s, int lvl);
	std::vector<std::string> _split(std::string &s, char c);
	std::string _serverNameCheck(std::string s);
	int _portCheck(std::string s);
	std::string _hostCheck(std::string s);
	void _rootCheck(std::string s);
	void _cmbzCheck(std::string s);
	void _errorPagesCheck(std::string s);
	void _locationCheck(std::string s);
	void _pathCheck(std::string s);
	void _aloowMethodsCheck(std::string s);
	void _Check(std::string s);
	void _uploadPathCheck(std::string s);
	void _autoindexCheck(std::string s);
	void _indexCheck(std::string s);
	void _cgiCheck(std::string s);
	void _redirectionCheck(std::string s);
	void _returnCheck(std::string s);
	void _rndmNbCheck(std::string s);

public:
	parser(int ac, char **av);
	void _runparser();
	~parser();
};

#endif