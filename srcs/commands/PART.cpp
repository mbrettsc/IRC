#include "../../includes/Server.hpp"

void Server::Part(std::vector<std::string>& param, Client& cli)
{
    passChecker(cli);
    if (param.size() > 2)
        Utils::writeMessage(cli.cliFd, ERR_NEEDMOREPARAMS(cli.nick, param[0]));
    else if (isChannelExist(param[0]))
    {
        for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
            if (it->_name == param[0]) {
                for (cliIt it2 = it->_channelClients.begin(); it2 != it->_channelClients.end(); ++it2) {
                    if (it2->nick == cli.nick) {
                        Utils::writeMessage(cli.cliFd, RPL_PART(cli.nick, param[0]));
                        it->_channelClients.erase(it2);
                        if (it->_channelClients.size() > 0)
                            it->op = &it->_channelClients[0];
                        std::cout << "Client " << cli.nick << " has left channel " << param[0] << std::endl;
                        break;
                    }
                }
                showRightGui(cli, *it);
                Utils::writeMessage(cli.cliFd, RPL_PART(cli.getPrefix(), param[0]));
            }
        }
    }
    else    
        Utils::writeMessage(cli.cliFd, ERR_NOSUCHCHANNEL(param[0], param[1]));
}
