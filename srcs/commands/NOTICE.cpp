#include "../../includes/Server.hpp"

void Server::BotNotice(std::vector<std::string>& params, Client& cli)
{
    std::string msg = "";
    for (size_t i = 0; i < params.size(); ++i) {
        msg += params[i] + " ";
    }
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->_isCap != BOT && it->_nick != params[1])
            Utils::writeMessage(it->_cliFd, RPL_NOTICE(cli._nick, params[1], msg));
    }
}

void Server::Notice(std::vector<std::string>& params, Client& cli)
{
    passChecker(cli);
    if (params[0] == "*") {
        BotNotice(params, cli);
        return ;
    }
    if (params[0][0] == '#') {
        Utils::writeMessage(cli._cliFd, "Cannot notice a channel\r\n");
        return ;
    }
    if (params.size() < 2) {
        Utils::writeMessage(cli._cliFd, ERR_NEEDMOREPARAMS(cli._nick, "NOTICE"));
        return ;
    }
    if (cli._nick == params[0]) {
        Utils::writeMessage(cli._cliFd, "Cannot notice yourself\r\n");
        return ;
    }
    size_t flag = 0;
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->_nick == params[0])
        {
            if (params[1][0] == ':')
                getAfterColon(params);
            flag = 1;
            it->_messageBox.push_back(RPL_NOTICE(cli._nick, params[0], params[1]));
            FD_SET(it->_cliFd, &_writeFds);
            break;
        }
    }
    if (flag == 0) {
        Utils::writeMessage(cli._cliFd, ERR_NOSUCHNICK);
    }
}
