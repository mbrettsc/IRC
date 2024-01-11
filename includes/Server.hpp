#pragma once

// Singleton design pattern

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <vector>
#include <fcntl.h>
#include "Client.hpp"

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
    // methods
    Server();
    static Server* singleton;
    void createSocket();
    void bindSocket(size_t const & port);
    void setPort(size_t const& port);
    void setPassword(std::string const& password);
    void printStatus();
    void acceptRequest();
    void readEvent();
    void initFds();
    void run();
public:
    ~Server();
    static int portIsValid(std::string const& port);
    void manageServer(size_t const & port, std::string const & password);
    static Server* getInstance();
};
