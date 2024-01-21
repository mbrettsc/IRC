#include "../../includes/Server.hpp"

void Server::User(std::vector<std::string>& param, Client& cli)
{
    if (cli.isCap == NC)
        passChecker(cli);
    if (param.size() < 4)
        Utils::writeMessage(cli.cliFd, ERR_NEEDMOREPARAMS(cli.nick, param[0]));
    else if (!cli.user.empty())
        Utils::writeMessage(cli.cliFd, ERR_ALREADYREGISTRED);
    else {
        cli.user = param[0];
        cli.host = param[1];
        cli.ip = param[2];
        if (param[3][0] != ':')
            cli.realName = param[3];
        else {
            size_t i = 3;
            while (i < param.size()) {
                cli.realName += param[i];
                if (i != param.size() - 1)
                    cli.realName += " ";
                ++i;
            }
            cli.realName.erase(0, 1);
        }
        std::cout << cli.realName << std::endl;
    }
}
