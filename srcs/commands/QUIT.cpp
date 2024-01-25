#include "../../includes/Server.hpp"

void Server::Quit(std::vector<std::string>& params, Client& cli)
{
    passChecker(cli);
    if (params[0] == "")
        std::cout << RED << "Client " << cli._nick << " quit" << RESET << std::endl;
    else
        std::cout << RED << "Client " << cli._nick << " quit (" << params[0] << ")" << RESET << std::endl;
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
            if (it->_nick == cli._nick)
            {
                for (chanIt itc = _channels.begin(); itc != _channels.end(); ++itc) {
                    for (cliIt it2 = itc->_channelClients.begin(); it2 != itc->_channelClients.end(); ++it2) {
                        if (it2->_nick == cli._nick)
                        {
                            int flag = 0;
                            itc->_channelClients.erase(it2);
                            if (itc->_channelClients.size() > 0)
                                itc->_opNick = itc->_channelClients[0]._nick;
                            else if (itc->_channelClients.size() == 0) {
                                _channels.erase(itc);
                                flag = 1;
                            }
                            Utils::writeMessage(cli._cliFd, RPL_QUIT(cli._nick, params[0].c_str()));
                            kickClient(it);
                            if (flag == 0)
                                showRightGui(cli, *itc);
                            return ;
                        }
                    }
                }
                Utils::writeMessage(cli._cliFd, RPL_QUIT(cli._nick, params[0].c_str()));
                kickClient(it);
                return;
            }
    }
}
