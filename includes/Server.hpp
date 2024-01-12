#pragma once

// Singleton design pattern

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <vector>
#include <map>
#include <fcntl.h>
#include "Client.hpp"

class Server;
typedef int (Server::*CmdFunct)(std::vector<std::string>& , Client&);

class Server
{
private:
    // variables
    int _serverFd;
    size_t _port;
    std::string _password;
    std::vector<Client> _clients;
    char buffer[1024];
    // fd_set's
    fd_set _readFds;
    fd_set _writeFds;
    fd_set _readFdsSup;
    fd_set _writeFdsSup;
    std::map<std::string, CmdFunct> t_cmdFunct;
    // methods
    Server();
    static Server* singleton;
    void createSocket();
    void bindSocket(size_t const&);
    void setPort(size_t const&);
    void setPassword(std::string const&);
    void printStatus();
    void acceptRequest();
    void readEvent();
    void initFds();
    void initCommands();
    void run();
    void kickClient(std::string const&, cliIt);
    void commandHandler(std::string&, Client&);
    // commands
    int Pass(std::vector<std::string>&, Client&);
    int Nick(std::vector<std::string>&, Client&);
    
public:
    ~Server();
    static int portIsValid(std::string const&);
    void manageServer(size_t const &, std::string const &);
    static Server* getInstance();
};
