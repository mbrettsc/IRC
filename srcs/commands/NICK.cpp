#include "../../includes/Server.hpp"

int Server::Nick(std::vector<std::string>& param, Client& cli)
{
    if (cli.passcheku && param.size() == 1)
        cli.nick = param[0];
    return 0;
}
