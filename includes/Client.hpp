#pragma once

#include <iostream>
#include <sys/types.h>
#include <arpa/inet.h>

#define NC 0
#define HEX 1

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

    int         isCap;
    int         passChecked;
    std::string buffer;

    Client();
};
