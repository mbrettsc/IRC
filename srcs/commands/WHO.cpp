#include "../../includes/Server.hpp"

int Server::isChannelExist(std::string const& channelName)
{
    for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if (it->_name == channelName)
            return 1;
    }
    return 0;
}

void Server::Who(std::vector<std::string>& param, Client& cli)
{
    if (cli.isCap == NC)
        passChecker(cli);
    std::cout << param.size() << std::endl;
    if (param.size() > 1)
        return ;
    if (isChannelExist(param[0]) == false)
        Utils::writeMessage(cli.cliFd,"No such channel\r\n");
    for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        std::cout << it->_name << " " << param[0] << std::endl;
        if (it->_name == param[0])
        {
            Utils::writeMessage(cli.cliFd, "Users in channel:\r\n");
            for (cliIt it2 = it->_channelClients.begin(); it2 != it->_channelClients.end(); ++it2) {
                std::cout << "* " + it2->nick + "\r\n" << std::endl;
                Utils::writeMessage(cli.cliFd, "* " + it2->nick + "\r\n");
            }
            return;
        }
    }
}
