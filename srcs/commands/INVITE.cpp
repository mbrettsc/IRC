#include "../../includes/Server.hpp"

void Server::Invite(std::vector<std::string>& param, Client& cli)
{
    if (isChannelExist(param[1]) == 0) {
        Utils::writeMessage(cli.cliFd, ERR_NOSUCHCHANNEL(param[1], param[0]));
        return ;
    }
    size_t flag = 0;
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->nick == param[0])
        {
            flag = 1;
            Channel chan = getChannel(param[1]);
            if (cli.nick != chan.op->nick) {
                Utils::writeMessage(cli.cliFd, ERR_CHANOPRIVSNEEDED(cli.nick, param[1]));
                return ;
            }
            Utils::writeMessage(it->cliFd, RPL_INVITE(cli.nick, cli.ipAddr, chan._name, param[1]));
        }
    }
    if (flag == 0)
        Utils::writeMessage(cli.cliFd, ERR_NOSUCHNICK);
}
