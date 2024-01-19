#pragma once

#include <vector>
#include <iostream>
#include "../includes/Client.hpp"

class Channel
{
public:
    std::string _name;
    std::string _topic;
    std::string _key;
    size_t userLimit;
    Client* op;
    std::vector<Client> _channelClients;
    std::vector<std::string> _bannedClients;
    Channel() : _key(""),  userLimit(0), op(NULL) {}


    std::vector<int> getFds()
    {
        std::vector<int> fds;
        for (std::vector<Client>::iterator it = _channelClients.begin(); it != _channelClients.end(); ++it)
            fds.push_back(it->cliFd);
        return fds;
    }
};
