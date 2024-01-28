#include "../../includes/Server.hpp"

void Server::Quit(std::vector<std::string>& params, Client& cli)
{
    if (params[0] == "")
        std::cout << RED << "Client " << cli._nick << " quit" << RESET << std::endl;
    else
        std::cout << RED << "Client " << cli._nick << " quit (" << params[0] << ")" << RESET << std::endl;
    cliIt baseIt = _clients.begin();
    for (baseIt = _clients.begin(); baseIt != _clients.end(); ++baseIt) {
        if (baseIt->_nick == cli._nick)
            break;
    }
    int flag;
    chanIt itChan = _channels.begin();
    while (itChan != _channels.end())
    {
        flag = 0;
        for (cliIt itClient = itChan->_channelClients.begin(); itClient != itChan->_channelClients.end(); ++itClient) {
            if (itClient->_nick != baseIt->_nick)
                continue;
            itChan->_channelClients.erase(itClient);
            if (itChan->_channelClients.size() > 0)
            {
                itChan->_opNick = itChan->_channelClients[0]._nick;
                showRightGui(cli, *itChan);
            }
            else if (itChan->_channelClients.size() == 0)
            {
                std::cout << RED << "Channel " << itChan->_name << " is deleted" << RESET << std::endl;
                _channels.erase(itChan);
                if (_channels.size() == 0)
                {
                    _channels.clear();
                    Utils::writeMessage(cli._cliFd, RPL_QUIT(cli._nick, params[0].c_str()));
                    kickClient(baseIt);
                    return;
                }
                itChan = _channels.begin();
                flag = 1;
            }
            break;
        }
        if (flag != 1)
            ++itChan;
    }
    Utils::writeMessage(cli._cliFd, RPL_QUIT(cli._nick, params[0].c_str()));
    kickClient(baseIt);
}
