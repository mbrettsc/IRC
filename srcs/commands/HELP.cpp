#include "../../includes/Server.hpp"

std::string returnHelp()
{
    std::string ret;

    ret += "First of all you need to enter Server Password with PASS command\r\n";
    ret += "Then you need to enter your nickname with NICK command\r\n";
    ret += "After that you can see the all commands with INFO command\r\n";
    ret += "ENJOY :)\r\n";

    return ret;
}

void Server::Help(std::vector<std::string>& params, Client& cli)
{
    (void)params;
    Utils::writeMessage(cli._cliFd, returnHelp());
}
