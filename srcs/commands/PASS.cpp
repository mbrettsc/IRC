#include "../../includes/Server.hpp"

void Server::Pass(std::vector<std::string>& param, Client& client)
{
    std::cout << "param 0 = " << param[0] << "password = " << _password << std::endl;
    if (param.empty())
        Utils::writeMessage(client.cliFd, ERR_NEEDMOREPARAMS);
    else if (client.passChecked == 1)
        Utils::writeMessage(client.cliFd, ERR_ALREADYREGISTRED);
    else if (param.size() == 1 && param[0] == _password)
        client.passChecked = 1;
    passChecker(client);
}
