#include "../../includes/Server.hpp"

void Server::Kick(std::vector<std::string>& params, Client& cli)
{
    passChecker(cli);
    if (params.size() < 2) {
        Utils::writeMessage(cli._cliFd, ERR_NEEDMOREPARAMS(cli._nick, params[0]));
        return ;
    }
    else if (params[1] == cli._nick) {
        Utils::writeMessage(cli._cliFd, ERR_CHANOPKICK(cli._nick, params[0]));
        return ;
    }
    else
    {
        int flag = 0;
        for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
            if (it->_name == params[0])
            {
                if (cli._nick != it->_opNick) {
                    Utils::writeMessage(cli._cliFd, ERR_CHANOPRIVSNEEDED(cli._nick, params[0]));
                    return ;
                }
                for (cliIt it2 = it->_channelClients.begin(); it2 != it->_channelClients.end(); ++it2) {
                    flag = 1;
                    if (it2->_nick == params[1]) {
                        std::string msg = "";
                        if (params.size() == 3)
                            msg = params[2];
                        Utils::writeMessage(it2->_cliFd, RPL_KICK(it->_opNick, params[0], params[1], msg));
                        Utils::writeMessage(it2->_cliFd, RPL_ENDOFNAMES(it2->_nick, params[0]));
                        it->_channelClients.erase(it2);
                        showRightGui(cli, *it);
                        return ;
                    }
                }
            }
        }
        if (flag == 0)
            Utils::writeMessage(cli._cliFd, ERR_NOSUCHCHANNEL(cli._nick, params[0]));
        else if (flag == 1)
            Utils::writeMessage(cli._cliFd, ": 431 " + cli._nick + " " + params[0] + " : " +  params[1] + " not in this channel\r\n");
    }
}
