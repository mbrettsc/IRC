#pragma once

// Singleton design pattern

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

class Server
{
private:
    int fd;
    Server();
    static Server* serverPtr;
public:
    ~Server();
    static Server* getInstance();
    int getFd() const {return fd;}
};
