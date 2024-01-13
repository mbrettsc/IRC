#pragma once

#include <vector>
#include <iostream>
#include "../includes/Client.hpp"

class Channel
{
private:
    std::string _name;
    std::string _topic;
    std::string _key;
    std::vector<std::string> _messageBox;
    std::vector<Client> _channelClients;
    Client* op;
public:
    Channel() : _key(""), op(NULL) {}
    std::string const& getName() const;
    std::string const& getKey() const;
    void setName(std::string const&);
    void setKey(std::string const&);
    void addClient(Client&);
    void setOp();
};
