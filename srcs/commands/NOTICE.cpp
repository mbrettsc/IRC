#include "../../includes/Server.hpp"

void Server::Notice(std::vector<std::string>& param, Client& cli)
{
    if (param[0][0] == '#') {
        Utils::writeMessage(cli.cliFd, "Cannot notice a channel\r\n");
        return ;
    }
    if (param.size() < 2) {
        Utils::writeMessage(cli.cliFd, ERR_NEEDMOREPARAMS(cli.nick, "NOTICE"));
        return ;
    }
    if (cli.nick == param[0]) {
        Utils::writeMessage(cli.cliFd, "Cannot notice yourself\r\n");
        return ;
    }
    size_t flag = 0;
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->nick == param[0])
        {
            if (param[1][0] == ':')
                getAfterColon(param);
            flag = 1;
            it->_messageBox.push_back(RPL_NOTICE(cli.nick, param[0], param[1]));
            FD_SET(it->cliFd, &_writeFds);
            break;
        }
    }
    if (flag == 0) {
        Utils::writeMessage(cli.cliFd, ERR_NOSUCHNICK);
    }
}
