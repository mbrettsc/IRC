#include "../../includes/Server.hpp"

void Server::Part(std::vector<std::string>& param, Client& cli)
{
    if (param.size() != 2)
        Utils::writeMessage(cli.cliFd, ERR_NEEDMOREPARAMS);
    if (isChannelExist(param[0]))
    {
        for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
            if (it->_name == param[0]) {
                for (cliIt it2 = it->_channelClients.begin(); it2 != it->_channelClients.end(); ++it2) {
                    if (it2->nick == cli.nick) {
                        Utils::writeMessage(cli.cliFd, RPL_PART(cli.nick, param[0]));
                        it->_channelClients.erase(it2);
                        break;
                    }
                }
                Utils::writeAllMessage(it->getFds(), RPL_NAMREPLY(cli.nick, param[0], ""));
                Utils::writeAllMessage(it->getFds(), RPL_ENDOFNAMES(cli.nick, param[0]));
                // for (cliIt it2 = it->_channelClients.begin(); it2 != it->_channelClients.end(); ++it2) {
                //     Utils::writeMessage(it2->cliFd, RPL_NAMREPLY(cli.nick, param[0], ""));
            }
        }
    }
    else    
        Utils::writeMessage(cli.cliFd, ERR_NOSUCHCHANNEL(param[0]));
}
