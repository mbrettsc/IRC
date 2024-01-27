#include "../../includes/Server.hpp"

void Server::Part(std::vector<std::string>& params, Client& cli)
{
    passChecker(cli);
    if (params.size() > 2)
        Utils::writeMessage(cli._cliFd, ERR_NEEDMOREPARAMS(cli._nick, params[0]));
    else if (isChannelExist(params[0]))
    {
        for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
            if (it->_name == params[0]) {
                for (cliIt it2 = it->_channelClients.begin(); it2 != it->_channelClients.end(); ++it2) {
                    if (it2->_nick == cli._nick) {
                        Utils::writeMessage(cli._cliFd, RPL_PART(cli._nick, params[0]));
                        it->_channelClients.erase(it2);
                        if (it->_channelClients.size() > 0)
                            it->_opNick = it->_channelClients[0]._nick;
                        std::cout << RED << "Client " << cli._nick << " has left channel " << params[0] << RESET << std::endl;
                        break;
                    }
                }
                if (it->_channelClients.size() == 0) {
                    std::cout << RED << "Channel " << it->_name << " is deleted" << RESET << std::endl;
                    _channels.erase(it);
                }
                else
                    showRightGui(cli, *it);
                Utils::writeMessage(cli._cliFd, RPL_PART(cli._nick, params[0]));
                break;
            }
        }
    }
    else    
        Utils::writeMessage(cli._cliFd, ERR_NOSUCHCHANNEL(params[0], params[1]));
}
