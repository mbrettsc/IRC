#include "../../includes/Server.hpp"

void Server::Oper(std::vector<std::string>& params, Client& cli)
{
    passChecker(cli);
    if (params.size() != 2) {
        Utils::writeMessage(cli._cliFd, ERR_NEEDMOREPARAMS(params[0], cli._nick));
        return ;
    }
    std::string chan = params[0];
    std::string name = params[1];
    params.clear();
    params.push_back(chan);
    params.push_back("+o");
    params.push_back(name);
    (this->*_commands["MODE"])(params, cli);
}
