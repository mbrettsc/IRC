#pragma once

#include <iostream>
#include <sys/types.h>
#include <arpa/inet.h>
#include <vector>

#define NC 0
#define HEX 1
#define BOT 2

class Client
{
    public:
        // variables
        int _cliFd;
        int _port;
        int _isCap;
        int _passChecked;
        char _ipAddr[INET_ADDRSTRLEN];
        std::string _buffer;
        std::string _user;
        std::string _host;
        std::string _ip;
        std::string _realName;
        std::string _nick;
        std::vector<std::string> _messageBox;
        // methods
        Client(): _isCap(0), _passChecked(0) {}
};
