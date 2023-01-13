#ifndef __INC_HPP__
#define __INC_HPP__

//exception errors
#define STOI_ERROR "stoi: no conversion"

//config file syntax error
#define BRACES_ERROR "Error: Curly braces are not written well in the configuration file or a server identifier used with no definition"
#define TAB_ERROR "Tab found in file, please run this command:\nexpand -t 2 'yourFileName' 'newFileName'"
#define EXTENTION_ERROE "Error: Wrong file extention configfile should have \".conf\" extention"
#define SEMI_COLON_ERROR "Error: missing semi colon one line: "
#define SPACE_ERROR "Error: missconfigured spaces in this line -> "
#define TOKEN_ERROR "Error: unrecognized token in this line -> "
#define FILE_ERROR "Invalid file name"
#define GEN_ERROR "Error: misconfigured file"

//leverl 1 tokens
#define LVL1_SRV_NAME "server_name"
#define LVL1_PORT "listen"
#define LVL1_HOST "host"
#define LVL1_ROOT "root"
#define LVL1_CMBZ "client_max_body_size"
#define LVL1_ERR_PAGE "error_page"
#define LVL1_LOCATION "location"

//level 2 tokens
#define LVL2_PATH "path"
#define LVL2_METHODS "allow_methods"
#define LVL2_ROOT "root"
#define LVL2_UPLOAD "upload_path"
#define LVL2_AUTOINDEX "autoindex"
#define LVL2_INDEX "index"
#define LVL2_CGI "cgi_info"
#define LVL2_REDIR "redirection"
#define LVL2_RETURN "return"

//lever 3 tokens xD
#define LVL2_3_RNDM_N "random_nb"

//tokens nd leverls
#define LVL1_TOKEN_N 7
#define LVL2_TOKEN_N 9
#define LVL3_TOKEN_N 1

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <exception>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>

#endif