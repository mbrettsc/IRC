#include "../includes/Channel.hpp"
#include "../includes/Server.hpp"

std::vector<int> Channel::getFds() const
{
    std::vector<int> fds;
    for (std::vector<Client>::const_iterator it = _channelClients.begin(); it != _channelClients.end(); ++it)
        fds.push_back(it->_cliFd);
    return fds;
}
