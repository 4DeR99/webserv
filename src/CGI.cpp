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

void fill_env(std::map<std::string, std::string> &env, Request &request, ServerConf &serverConf, Location &location)
{
	env["REQUEST_METHOD"] = method2String(request.getType());
	env["SERVER_PROTOCOL"] = "HTTP/1.1";
	env["SERVER_SOFTWARE"] = "webserv";
	env["GATEWAY_INTERFACE"] = "CGI/1.1";
	env["SERVER_ADDR"] = serverConf.getHost();
	env["SCRIPT_NAME"] = request.getUrl();
	env["SCRIPT_FILENAME"] = request.getUrl().substr(request.getUrl().find_last_of('/') + 1);
	env["SERVER_NAME"] = serverConf.getSrvname();
	env["SERVER_PORT"] = serverConf.getPort().front();
	env["PATH_INFO"] = location.getRoot();
	env["CONTENT_TYPE"] = request.getHeaders()["Content-Type"];
	env["CONTENT_LENGTH"] = std::to_string(request.getBodyLength());
	env["QUERY_STRING"] = request.getQueryString();
	env["HTTP_COOKIE"] = request.getHeaders()["cookie"];
	env["REDIRECT_STATUS"] = "200";
	for (std::map<std::string, std::string>::iterator it = request.getHeaders().begin(); it != request.getHeaders().end(); it++)
	{
		env["HTTP_" + it->first] = it->second;
	}
}

char **map2tab(std::map<std::string, std::string> &env)
{
	char **envp = new char *[env.size() + 1];
	int i = 0;
	for (std::map<std::string, std::string>::iterator it = env.begin(); it != env.end(); it++, i++)
	{
		std::string tmp = it->first + "=" + it->second;
		envp[i] = new char[tmp.size() + 1];
		envp[i] = std::strcpy(envp[i], tmp.c_str());
	}
	envp[i] = NULL;
	return envp;
}

std::string execCgi(Request &request, ServerConf &serverConf, Location &location)
{
	std::map<std::string, std::string> env;
	std::string cgi_path = location.getCgi();
	fill_env(env, request, serverConf, location);
	std::string response;
	char buffer[1024];
	char *_args[3];
	FILE *tmp_in = tmpfile();
	FILE *tmp_out = tmpfile();
	FILE *tmp_err = tmpfile();
	int in = fileno(tmp_in);
	int out = fileno(tmp_out);
	int err = fileno(tmp_err);
	_args[0] = (char *)cgi_path.c_str();
	_args[1] = (char *)env["SCRIPT_FILENAME"].c_str();
	_args[2] = NULL;
	write(in, request.getBody().c_str(), request.getBodyLength());
	lseek(in, 0, SEEK_SET);
	char **envp = map2tab(env);
	int pid = fork();
	if (pid == -1)
		throw std::runtime_error("internal server error");
	else if (pid == 0)
	{
		dup2(in, 0);
		dup2(out, 1);
		dup2(err, 2);
		if (chdir(request.getAbsoluteUrl().substr(0, request.getAbsoluteUrl().find_last_of('/')).c_str()) == -1)
		{
			forup(i, 0, env.size()) delete[] envp[i];
			delete[] envp;
			throw std::runtime_error("internal server error");
		}
		if (execve(_args[0], (char **)_args, envp) == -1)
		{
			forup(i, 0, env.size()) delete[] envp[i];
			delete[] envp;
			std::cout << "execve error" << std::endl;
			throw std::runtime_error("internal server error");
		}
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
		if (status != 0)
		{
			forup(i, 0, env.size()) delete[] envp[i];
			delete[] envp;
			throw std::runtime_error("internal server error");
		}
		lseek(out, 0, SEEK_SET);
		int ret;
		while ((ret = read(out, buffer, 1024)) > 0)
			response.append(buffer, ret);
	}
	fclose(tmp_in);
	fclose(tmp_out);
	close(in);
	close(out);
	forup(i, 0, env.size()) delete[] envp[i];
	delete[] envp;
	return response;
}