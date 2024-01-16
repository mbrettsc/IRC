#include "../../includes/Server.hpp"

void Server::Quit(std::vector<std::string>& param, Client& cli)
{
    if (param.empty())
        std::cout << "Client " << cli.nick << " quit" << std::endl;
    else
        std::cout << "Client " << cli.nick << " quit (" << param[0] << ")" << std::endl;
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
            if (it->nick == cli.nick) {
                kickClient(it);
                break;
            }
    }
}
