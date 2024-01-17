#include "../../includes/Server.hpp"

void Server::Privmsg(std::vector<std::string>& param, Client& cli)
{
    int flag = 0;

    if (param.size() < 2) {
        Utils::writeMessage(cli.cliFd, ERR_NEEDMOREPARAMS);
        return ;
    }
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
        if (param[0] == it->nick) {
            if (param[1][0] == ':') {
                param[1].erase(0, 1);
                for (size_t i = 1; i < param.size(); ++i) {
                    param[1] += " " + param[i];
                }
            }
            std::string msg = ":" + cli.nick + " PRIVMSG " + param[0] + " :" + param[1] + "\r\n";
            it->_messageBox.push_back(msg);
            FD_SET(it->cliFd, &_writeFds);
            flag = 1;
            return ;
        }
    }
    if (flag == 0)
        Utils::writeMessage(cli.cliFd, ERR_NOSUCHNICK);
}
