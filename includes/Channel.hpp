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
    std::string opNick;
    std::vector<Client> _channelClients;
    Channel() : _topic(""), _key(""),  userLimit(0), opNick("") {}


    std::vector<int> getFds() const;
};
