#include "../../includes/Server.hpp"

void Server::Pass(std::vector<std::string>& param, Client& client)
{
    if (param.size() != 1)
        Utils::writeMessage(client.cliFd, ERR_NEEDMOREPARAMS(param[0], _password));
    else if (client.passChecked == 1)
        Utils::writeMessage(client.cliFd, ERR_ALREADYREGISTRED);
    else if (param[0] == _password)
        client.passChecked = 1;
    passChecker(client);
}
