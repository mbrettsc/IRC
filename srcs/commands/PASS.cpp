#include "../../includes/Server.hpp"

void Server::Pass(std::vector<std::string>& params, Client& cli)
{
    if (params.size() != 1)
        Utils::writeMessage(cli._cliFd, ERR_NEEDMOREPARAMS(params[0], _password));
    else if (cli._passChecked == 1)
        Utils::writeMessage(cli._cliFd, ERR_ALREADYREGISTRED);
    else if (params[0] == _password)
    {
        cli._passChecked = 1;
        Utils::writeMessage(cli._cliFd, Utils::welcome());
    }
    passChecker(cli);
}
