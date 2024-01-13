#include "../includes/Channel.hpp"

std::string const & Channel::getName() const
{
    return _name;
}

std::string const & Channel::getKey() const
{
    return _key;
}

void Channel::setName(std::string const& name)
{
    _name = name;
}

void Channel::setKey(std::string const& key)
{
    _key = key;
}

void Channel::setOp()
{
    op = &(*_channelClients.begin());
}

void Channel::addClient(Client& cli)
{
    _channelClients.push_back(cli);
}
