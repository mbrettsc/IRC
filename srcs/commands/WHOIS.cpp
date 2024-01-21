#include "../../includes/Server.hpp"

void Server::Whois(std::vector<std::string>& param, Client& cli)
{
    passChecker(cli);
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->nick == param[0]) {
            Utils::writeMessage(cli.cliFd, RPL_WHOISUSER(it->nick, it->user, it->ip));
            Utils::writeMessage(cli.cliFd, RPL_WHOISSERVER(it->nick, "Rote Flaggen"));
            Utils::writeMessage(cli.cliFd, RPL_ENDOFWHOIS(it->nick, it->nick));
            return;
        }        
    }
}
