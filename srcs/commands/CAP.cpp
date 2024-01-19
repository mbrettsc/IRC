#include "../../includes/Server.hpp"

void Server::Cap(std::vector<std::string>& param, Client& cli)
{
    if (param[0] == "LS")
        cli.isCap = 1;
}
