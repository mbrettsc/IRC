#pragma once

// Singleton design pattern

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

class Server
{
private:
    int _sockFd;
    std::string _password;
    Server();
    static Server* singleton;
    void createSocket();
    void bindSocket(size_t const & port);
public:
    ~Server();
    static int portIsValid(std::string const& port);
    void setPassword(std::string const& password);
    void manageServer(size_t const & port, std::string const & password);
    static Server* getInstance();
};
