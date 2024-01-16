#include "../../includes/Server.hpp"

void Server::User(std::vector<std::string>& param, Client& cli)
{
    if (param.size() < 4)
        Utils::writeMessage(cli.cliFd, ERR_NEEDMOREPARAMS);
    else if (!cli.user.empty())
        Utils::writeMessage(cli.cliFd, ERR_ALREADYREGISTRED);
    else {
        cli.user = param[0];
        cli.ip = param[3];
    }
}
