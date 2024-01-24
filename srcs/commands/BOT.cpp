#include "../../includes/Server.hpp"

void Server::Bot(std::vector<std::string>& params, Client& cli)
{
    if (cli._isCap == NC)
        passChecker(cli);
    if (params.size() != 1) {
        Utils::writeMessage(cli._cliFd, ERR_NEEDMOREPARAMS(cli._nick, "BOT"));
        return ;
    }
    if (_botFd == 0) {
        Utils::writeMessage(cli._cliFd, "Bot is not connected\r\n");
        return ;
    }
    Utils::writeMessage(_botFd, "bot " + cli._nick + " " + params[0] + "\r\n");
}
