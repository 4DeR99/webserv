#ifndef __INC_HPP__
#define __INC_HPP__

//? exception errors
#define STOI_ERROR "stoi: no conversion"

#define forup(i, x, y) for (size_t i = x; i < y; i++)

//? config file syntax error
#define TAB_ERROR "Tab found in file, please run this command:\nexpand -t 2 'yourFileName' 'newFileName'"
#define EXTENTION_ERROE "Error: Wrong file extention configfile should have \".conf\" extention"
#define SPACE_ERROR "Error: missconfigured spaces in this line -> "
#define TOKEN_ERROR "Error: unrecognized token in this line -> "
#define FILE_ERROR "Invalid file name"
#define GEN_ERROR "Error: misconfigured file"
#define SRVNAME_ERROR "Error: invalid server name"
#define PORT_ERROR "Error: invalid port"
#define HOST_ERROR "Error: invalid host"
#define CMBZ_ERROR "Error: invalid client max body size"
#define ERRPAGETOKEN_ERROR "Error: error_page token should end with a colon"
#define ERRPAGE_ERROR "Error: invalid error page"
#define LOCATION_ERROR "Error: location token should end with a colon"
#define PATHFRNT_ERROR "Error: you should start your path with a /"
#define PATH_ERROR "Error: cant have 1 path in multiple locations"
#define AUTOINDEX_ERROR "Error: autoindex should be only on or off"
#define ALMETHODS_ERROR "Error: invalid allow methods"
// #define RETURN_ERROR "Error: invalid return configuration"
#define PORT_MISSING "Error: port missing"
#define ROOT_MISSING "Error: root missing"
#define PATH_MISSING "Error: path missing on a location"
#define REDIRECTION_ERROR "Error: invalid redirection configuration"
#define UPLOADPATH_ERROR "Error: invalid upload path"
#define ROOT_ERROR "Error: invalid root"
#define CGI_ERROR "Error: invalid cgi info"
#define REDIR_ERROR "Error: invalid redirection"
#define DOUBLE_PORT "Error: cant have more than 1 port in a server"
#define DOUBLE_HOST "Error: cant have more than 1 host in a server"
#define DOUBLE_ROOT "Error: cant have more than 1 root in a server"
#define DOUBLE_SRVNAME "Error: cant have more than 1 server name"
#define DOUBLE_PATH "Error: cant have more than 1 location path"
#define DOUBLE_UPLOADPATH "Error: cant have more than 1 upload path in a location"
#define DOUBLE_INDEX "Error: cant have more than 1 index in a location"
#define DOUBLE_AUTOINDEX "Error: cant set autoindex more than once in a location"
#define DOUBLE_REDIRECTION "Error: cant overrider a redirection in a location"
#define DOUBLE_RETURN "Error: cant overrider a return in a location"
#define DOUBLE_ALLOWMETHODS "Error: cant set the allowed methods more than 1 time in a location"
#define DOUBLE_CGI "Error: cant set cgi info more than 1 time in a location"
#define DOUBLE_ERRPAGE "Error: cant override an error page"
#define DOUBLE_CMBZ "Error: cant have more than 1 client max body size"
#define DOUBLE_LOCATION_PATH "Error: cant have multiple locations with same path"

//? leverl 1 tokens
#define LVL1_SRV_NAME "server_name"
#define LVL1_PORT "listen"
#define LVL1_HOST "host"
#define LVL1_ROOT "root"
#define LVL1_CMBZ "clientMaxBodySize"
#define LVL1_ERR_PAGE "error_page"
#define LVL1_LOCATION "location"

//? level 2 tokens
#define LVL2_PATH "path"
#define LVL2_METHODS "allow_methods"
#define LVL2_ROOT "root"
#define LVL2_UPLOAD "upload_path"
#define LVL2_AUTOINDEX "autoindex"
#define LVL2_INDEX "index"
#define LVL2_CGI "cgi_info"
#define LVL2_REDIR "redirection"
#define LVL2_RETURN "return"

//? tokens nd leverls
#define LVL1_TOKEN_N 7
#define LVL2_TOKEN_N 8

#define LOCALHOST "127.0.0.1"

#define NGINX_MAX_BODY_SIZE 1048576

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <cerrno>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <exception>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <dirent.h>

#include "Location.hpp"
#include "Serverconf.hpp"
#include "Parser.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Client.hpp"
#include "Pollge.hpp"

#endif