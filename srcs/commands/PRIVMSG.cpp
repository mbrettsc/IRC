#include "../../includes/Server.hpp"

void Server::toChannel(std::vector<std::string>& params, Client& cli)
{
    if (isChannelExist(params[0]) == 0) {
        Utils::writeMessage(cli._cliFd, ERR_NOSUCHCHANNEL(params[0], params[1]));
        return ;
    }
    if (clientIsInThere(cli, params[0]) == 1)
    {
        if (params[1][0] == ':') {
            getAfterColon(params);
        }
        for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
            if (it->_nick != cli._nick && clientIsInThere(*it, params[0]) == 1) {
                it->_messageBox.push_back(RPL_PRIVMSG(cli._nick, params[0], params[1]));
                FD_SET(it->_cliFd, &_writeFds);
            }
        }
    }
}

void Server::toClient(std::vector<std::string>& params, Client& cli)
{
    int flag = 0;

    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
        if (params[0] == it->_nick) {
            if (params[1][0] == ':') {
               getAfterColon(params);
            }
            it->_messageBox.push_back(RPL_PRIVMSG(cli._nick, params[0], params[1]));
            FD_SET(it->_cliFd, &_writeFds);
            flag = 1;
            return ;
        }
    }
    if (flag == 0)
        Utils::writeMessage(cli._cliFd, ERR_NOSUCHNICK);
}

void Server::Privmsg(std::vector<std::string>& params, Client& cli)
{
    passChecker(cli);
    if (params.size() < 2)
    {
        Utils::writeMessage(cli._cliFd, ERR_NEEDMOREPARAMS(cli._nick, params[0]));
        return ;
    }
    else if (params[0][0] == '#')
        toChannel(params, cli);
    else
        toClient(params, cli);
}
