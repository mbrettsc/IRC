#include "../../includes/Server.hpp"

void Server::Quit(std::vector<std::string>& params, Client& cli)
{
    passChecker(cli);
    if (params.empty())
        std::cout << "Client " << cli._nick << " quit" << std::endl;
    else
        std::cout << "Client " << cli._nick << " quit (" << params[0] << ")" << std::endl;
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
            if (it->_nick == cli._nick) {
                Utils::writeMessage(cli._cliFd, RPL_QUIT(cli._nick, params[0].c_str()));
                kickClient(it);
                break;
            }
    }
}
