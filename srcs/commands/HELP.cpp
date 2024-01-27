#include "../../includes/Server.hpp"

std::string returnHelp()
{
    std::string ret;

    ret += "To get started, begin by entering your server password using the PASS command.\r\n";
    ret += "Next, set your nickname with the NICK command.\r\n";
    ret += "Explore available commands and features with the INFO command.\r\n";
    ret += "Enjoy your time on the server! :)\r\n";

    return ret;
}

void Server::Help(std::vector<std::string>& params, Client& cli)
{
    (void)params;
    Utils::writeMessage(cli._cliFd, returnHelp());
}
