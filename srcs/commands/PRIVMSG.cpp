#include "../../includes/Server.hpp"

void Server::toChannel(std::vector<std::string>& param, Client& cli)
{
    if (isChannelExist(param[0]) == 0) {
        Utils::writeMessage(cli.cliFd, ERR_NOSUCHCHANNEL(param[0], param[1]));
        return ;
    }
    if (clientIsInThere(cli, param[0]) == 1)
    {
        if (param[1][0] == ':') {
            param[1].erase(0, 1);
            for (size_t i = 2; i < param.size(); ++i) {
                param[1] += " " + param[i];
            }
        }
        for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
            if (it->nick != cli.nick && clientIsInThere(*it, param[0]) == 1) {
                std::string msg = ":" + cli.nick + " PRIVMSG " + param[0] + " :" + param[1] + "\r\n";
                it->_messageBox.push_back(msg);
                std::cout << "msg: " << it->_messageBox.size() << it->cliFd << std::endl;
                FD_SET(it->cliFd, &_writeFds);
            }
        }
    }
}

void Server::toClient(std::vector<std::string>& param, Client& cli)
{
    int flag = 0;

    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
        if (param[0] == it->nick) {
            if (param[1][0] == ':') {
                param[1].erase(0, 1);
                for (size_t i = 2; i < param.size(); ++i) {
                    param[1] += " " + param[i];
                }
            }
            std::string msg = ":" + cli.nick + " PRIVMSG " + param[0] + ": " + param[1] + "\r\n";
            it->_messageBox.push_back(msg);
            FD_SET(it->cliFd, &_writeFds);
            flag = 1;
            return ;
        }
    }
    if (flag == 0)
        Utils::writeMessage(cli.cliFd, ERR_NOSUCHNICK);
}

void Server::Privmsg(std::vector<std::string>& param, Client& cli)
{
    passChecker(cli);
    if (param.size() < 2)
    {
        Utils::writeMessage(cli.cliFd, ERR_NEEDMOREPARAMS(cli.nick, param[0]));
        return ;
    }
    else if (param[0][0] == '#')
        toChannel(param, cli);
    else
        toClient(param, cli);
}
