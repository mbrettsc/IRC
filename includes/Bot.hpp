#pragma once

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Utils.hpp"

class Bot
{
private:
    // variables
    int _fd;
    int _port;
    std::string _password;
    static Bot* singleton;
    // methods
    void setPort(int);
    void setPasword(std::string const&);
    void createSocket();
public:
    Bot(): _fd(0), _port(0), _password("") {};
    ~Bot();
    static Bot *getInstance();
    void run(int, std::string const&);
};
