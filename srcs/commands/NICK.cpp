#include "../../includes/Server.hpp"

void Server::Nick(std::vector<std::string>& params, Client& cli)
{
    if (cli._isCap == NC)
        passChecker(cli);
    if (params.size() == 1 && !isNickExist(params[0]) && !params[0].empty() && params[0].size() <= 9) {
        for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
            for (cliIt cit = it->_channelClients.begin(); cit != it->_channelClients.end(); ++cit) {
                if (cli._nick == cit->_nick)
                {
                    if (cit->_nick == it->_opNick)
                        it->_opNick = params[0];
                    cit->_nick = params[0];
                    break;
                }
            }
            Utils::writeMessage(cli._cliFd, RPL_NICK(cli._nick, cli._user, cli._ipAddr, params[0]));
            showRightGui(cli, *it);
        }
        cli._nick = params[0];
        Utils::writeMessage(cli._cliFd, RPL_NICK(cli._nick, cli._user, cli._ipAddr, params[0]));
    }
    else {
        if (params.size() != 1)
            Utils::writeMessage(cli._cliFd, ERR_NEEDMOREPARAMS(cli._nick, params[0]));
        else if (params[0].size() > 9)
            Utils::writeMessage(cli._cliFd, ERR_NONICKNAMEGIVEN);
        else if (params[0].empty())
            Utils::writeMessage(cli._cliFd, ERR_NICKNAMEEMPTY(cli._nick));
        else
            Utils::writeMessage(cli._cliFd, ERR_NICKNAMEINUSE(params[0]));
    }
}
