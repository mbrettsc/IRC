#include "../../includes/Server.hpp"

void Server::Nick(std::vector<std::string>& param, Client& cli)
{
    if (cli.isCap == NC)
        passChecker(cli);
    if (param.size() == 1 && !isNickExist(param[0]) && !param[0].empty() && param[0].size() <= 9) {
        Utils::writeMessage(cli.cliFd, RPL_NICK(cli.nick, cli.user, cli.ipAddr, param[0]));
        cli.nick = param[0];
    }
    else {
        if (param.size() != 1)
            Utils::writeMessage(cli.cliFd, ERR_NEEDMOREPARAMS);
        else if (param[0].size() > 9)
            Utils::writeMessage(cli.cliFd, ERR_NONICKNAMEGIVEN);
        else if (param[0].empty())
            Utils::writeMessage(cli.cliFd, ERR_NICKNAMEEMPTY(cli.nick));
        else
            Utils::writeMessage(cli.cliFd, ERR_NICKNAMEINUSE(cli.nick));
    }
}
