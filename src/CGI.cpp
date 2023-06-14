#include "../inc/Inc.hpp"

std::string method2String(int method)
{
  switch (method)
  {
  case GET:
    return "GET";
  case POST:
    return "POST";
  case DELETE:
    return "DELETE";
  default:
    return "UNKNOWN";
  }
}

void fill_env(std::map<std::string, std::string>&env, Request &request, ServerConf &serverConf, Location &location){
  env["REQUEST_METHOD"] = method2String(request.getType());
  env["SERVER_PROTOCOL"] = "HTTP/1.1";
  env["SCRIPT_NAME"] = request.getUrl();
  env["SERVER_NAME"] = serverConf.getSrvname();
  env["SERVER_PORT"] = serverConf.getPort();
  env["PATH_INFO"] = location.getRoot();
  env["CONTENT_TYPE"] = request.getHeaders()["Content-Type"];
  env["CONTENT_LENGTH"] = std::to_string(request.getBodyLength());
  
}

std::string CGI(Request &request, ServerConf &serverConf, Location &location){
  std::map<std::string, std::string> env;
  std::string cgi_path = location.getCgi();
  fill_env(env, request, serverConf, location);
}