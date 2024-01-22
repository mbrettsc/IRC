#include "../../includes/Server.hpp"

void Server::List(std::vector<std::string>& param, Client& cli)
{
    (void)param;
    Utils::writeMessage(cli.cliFd, RPL_LISTSTART(cli.nick, Utils::intToString(_clients.size())));
    for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
        std::string tmp = Utils::intToString(it->_channelClients.size());
        if (it->_topic == "")
            Utils::writeMessage(cli.cliFd, RPL_LIST(cli.nick, it->_name, tmp, "No topic"));
        else
            Utils::writeMessage(cli.cliFd, RPL_LIST(cli.nick, it->_name, tmp, it->_topic.c_str()));
    }
    Utils::writeMessage(cli.cliFd, RPL_LISTEND(cli.nick));
}
