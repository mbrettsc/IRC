#pragma once

#include <iostream>
#include <sys/types.h>


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

    Client() :isCapt(0), passcheku(0), buffer("")  {}
};

typedef std::vector<Client>::iterator cliIt;
