#include "../../includes/Server.hpp"

void Server::Who(std::vector<std::string>& params, Client& cli)
{
    passChecker(cli);
    if (params.size() > 1)
        return ;
    if (isChannelExist(params[0]) == false)
        Utils::writeMessage(cli._cliFd,"No such channel\r\n");
    for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if (it->_name == params[0])
        {
            Utils::writeMessage(cli._cliFd, "Users in this channel:\r\n");
            for (cliIt it2 = it->_channelClients.begin(); it2 != it->_channelClients.end(); ++it2) {
                Utils::writeMessage(cli._cliFd, "* " + it2->_nick + "\r\n");
            }
            return;
        }
    }
}
