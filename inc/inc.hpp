#ifndef __INC_HPP__
#define __INC_HPP__

#define BRACES_ERROR "Error: Curly braces are not written well in the configuration file or a server identifier used with no definition"
#define EXTENTION_ERROE "Error: Wrong file extention configfile should have \".conf\" extention"
#define SEMI_COLON_ERROR "Error: missing semi colon one line: "
#define SPACE_ERROR "Error: missconfigured spaces in this line ->"
#define TOKEN_ERROR "Error: unrecognized token in this line ->"
#define FILE_ERROR "Invalid file name"
#define GEN_ERROR "Error: misconfigured file"

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