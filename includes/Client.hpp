#pragma once

#include <iostream>
#include <sys/types.h>
#include <arpa/inet.h>

class Client
{
public:
    int cliFd;
    int port;
    char ipAddr[INET_ADDRSTRLEN];
    std::string ip;
    std::string user;
    std::string nick;
    std::string pass;

    int         isCapt;
    int         passcheku;
    std::string buffer;

    Client();
};

typedef std::vector<Client>::iterator cliIt;
