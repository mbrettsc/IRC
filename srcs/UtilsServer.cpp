#include "../includes/Server.hpp"

void Server::getAfterColon(std::vector<std::string>& param)
{
    param[1].erase(0, 1);
    for (size_t i = 2; i < param.size(); ++i) {
        param[1] += " " + param[i];
    }
}

Channel Server::getChannel(std::string const& channelName)
{
    chanIt it;
    for (it = _channels.begin(); it != _channels.end(); ++it) {
        if (it->_name == channelName) {
            break;
        }
    }
    return *it;
}

int Server::isChannelExist(std::string const& channelName)
{
    for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
        if (it->_name == channelName)
            return 1;
    }
    return 0;
}

int Server::clientIsInThere(Client& client, std::string const& chanName)
{
    for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
        if (it->_name == chanName)
        {
            for (cliIt it2 = it->_channelClients.begin(); it2 != it->_channelClients.end(); ++it2) {
                if (it2->nick == client.nick)
                    return (1);
            }
        }
    }
    return (0);
}

void Server::showRightGui(Client &cli, Channel &tmp) {
    std::string msg;
    if (tmp._name.empty())
        return;
    for(std::vector<Client>::iterator it = tmp._channelClients.begin() ; it != tmp._channelClients.end(); ++it) {
        if (it->cliFd == tmp.op->cliFd)
            msg += "@";
        msg += (*it).nick + " ";
    }
    Utils::writeAllMessage(tmp.getFds(), RPL_NAMREPLY(cli.nick, tmp._name, msg));
    Utils::writeAllMessage(tmp.getFds(), RPL_ENDOFNAMES(cli.nick, tmp._name));
}
