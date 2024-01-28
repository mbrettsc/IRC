#include "../../includes/Server.hpp"

void Server::List(std::vector<std::string>& params, Client& cli)
{
    passChecker(cli);
    (void)params;
    Utils::writeMessage(cli._cliFd, RPL_LISTSTART(cli._nick, Utils::intToString(_clients.size())));
    for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
        std::string tmp = Utils::intToString(it->_channelClients.size());
        if (it->_topic == "")
            Utils::writeMessage(cli._cliFd, RPL_LIST(cli._nick, it->_name, tmp, ":No topic is set"));
        else
            Utils::writeMessage(cli._cliFd, RPL_LIST(cli._nick, it->_name, tmp, it->_topic.c_str()));
    }
    Utils::writeMessage(cli._cliFd, RPL_LISTEND(cli._nick));
}
