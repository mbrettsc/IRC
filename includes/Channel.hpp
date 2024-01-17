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
    Client* op;
    std::vector<Client> _channelClients;
    Channel() : _key(""), op(NULL) {}
};
