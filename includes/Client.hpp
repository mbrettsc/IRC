#pragma once

#include <iostream>
#include <sys/types.h>
#include <arpa/inet.h>
#include <vector>

#define NC 0
#define HEX 1

class Client
{
public:
    int cliFd;
    int port;
    char ipAddr[INET_ADDRSTRLEN];
    std::string user;
    std::string host;
    std::string ip;
    std::string realName;
    std::string nick;
    std::vector<std::string> _messageBox;

    int         isCap;
    int         passChecked;

    Client():isCap(0), passChecked(0) {}
    std::string	        getPrefix() const;

};
