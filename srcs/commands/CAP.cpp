#include "../../includes/Server.hpp"

void Server::Cap(std::vector<std::string>& param, Client& cli)
{
    if (param[0] == "LS" && param.size() == 1)
        cli.isCap = 1;
}
