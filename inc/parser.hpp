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

public:
	parser(int ac, char **av);
	void _runparser();
	~parser();
};

#endif