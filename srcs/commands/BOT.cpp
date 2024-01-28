#include "../../includes/Server.hpp"

void Server::Bot(std::vector<std::string>& params, Client& cli)
{
    passChecker(cli);
    if (cli._nick == "") {
        Utils::writeMessage(cli._cliFd, "Set your nickname first\r\n");
        return ;
    }
    if (params[0] == "") {
        Utils::writeMessage(cli._cliFd, ERR_NEEDMOREPARAMS(cli._nick, "BOT"));
        return ;
    }
    if (_botFd == 0) {
        Utils::writeMessage(cli._cliFd, "Bot is not connected\r\n");
        return ;
    }
    std::string msg = "";
    for (size_t i = 0; i < params.size(); ++i) {
        msg += params[i] + " ";
    }
    Utils::writeMessage(_botFd, "bot " + cli._nick + " " + msg + "\r\n");
}
