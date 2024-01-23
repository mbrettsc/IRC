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
    void run();
    void execute(std::string const&);
public:
    Bot(): _fd(0), _port(0), _password("") {};
    ~Bot();
    // Bot(const Bot &);
    // Bot &operator=(const Bot &);
    static Bot *getInstance();
    void manageBot(int, std::string const&);
};
