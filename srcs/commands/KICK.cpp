#include "../../includes/Server.hpp"

void Server::Kick(std::vector<std::string>& param, Client& cli)
{
    passChecker(cli);
    if (param.size() < 2) {
        Utils::writeMessage(cli.cliFd, ERR_NEEDMOREPARAMS(cli.nick, param[0]));
        return ;
    }
    else if (param[1] == cli.nick) {
        Utils::writeMessage(cli.cliFd, ERR_CHANOPKICK(cli.nick, param[0]));
        return ;
    }
    else {
        int flag = 0;
       for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
        if (it->_name == param[0])
        {
            flag = 1;
            if (cli.nick != it->opNick) {
                Utils::writeMessage(cli.cliFd, ERR_CHANOPRIVSNEEDED(cli.nick, param[0]));
                return ;
            }
            for (cliIt it2 = it->_channelClients.begin(); it2 != it->_channelClients.end(); ++it2) {
                if (it2->nick == param[1]) {
                    flag = 2;
                    std::string msg = "";
                    if (param.size() == 3)
                        msg = param[3];
                    Utils::writeMessage(it2->cliFd, RPL_KICK(it->opNick, param[0], param[1], msg));
                    Utils::writeMessage(it2->cliFd, RPL_ENDOFNAMES(it2->nick, param[0]));
                    it->_channelClients.erase(it2);
                    showRightGui(cli, *it);
                    return ;
                }
            }
        }
       }
       if (flag == 0)
        Utils::writeMessage(cli.cliFd, ERR_NOSUCHCHANNEL(cli.nick, param[0]));
        else if (flag == 2)
            Utils::writeMessage(cli.cliFd, ERR_NOSUCHNICK);
    }
}