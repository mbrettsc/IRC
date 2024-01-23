#include "../../includes/Server.hpp"

void Server::User(std::vector<std::string>& params, Client& cli)
{
    if (cli._isCap == NC)
        passChecker(cli);
    if (params.size() < 4)
        Utils::writeMessage(cli._cliFd, ERR_NEEDMOREPARAMS(cli._nick, params[0]));
    else if (!cli._user.empty())
        Utils::writeMessage(cli._cliFd, ERR_ALREADYREGISTRED);
    else {
        cli._user = params[0];
        cli._host = params[1];
        cli._ip = params[2];
        if (params[3][0] != ':')
            cli._realName = params[3];
        else {
            size_t i = 3;
            while (i < params.size()) {
                cli._realName += params[i];
                if (i != params.size() - 1)
                    cli._realName += " ";
                ++i;
            }
            cli._realName.erase(0, 1);
        }
    }
}
