#include "../../includes/Server.hpp"

int Server::Pass(std::vector<std::string>& param, Client& client)
{
    if (param.empty())
        Utils::writeMessage(client.cliFd, ERR_NEEDMOREPARAMS);
    else if (client.passcheku == 1)
        Utils::writeMessage(client.cliFd, ERR_ALREADYREGISTRED);
    else if (param.size() == 1 && param[0] == _password)
        client.passcheku = 1;
    return 0;
}
