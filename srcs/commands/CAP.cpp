#include "../../includes/Server.hpp"

void Server::Cap(std::vector<std::string>& params, Client& cli)
{
    if (params[0] == "LS")
        cli._isCap = HEX;
    else if (params[0] == "BOT")
    {
        cli._isCap = BOT;
        _botFd = cli._cliFd;
    }
    else
        cli._isCap = NC;
}
