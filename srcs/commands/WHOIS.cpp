#include "../../includes/Server.hpp"

void Server::Whois(std::vector<std::string>& params, Client& cli)
{
    passChecker(cli);
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->_nick == params[0]) {
            Utils::writeMessage(cli._cliFd, RPL_WHOISUSER(it->_nick, it->_user, it->_ip));
            Utils::writeMessage(cli._cliFd, RPL_WHOISSERVER(it->_nick, "Rote Flaggen"));
            Utils::writeMessage(cli._cliFd, RPL_ENDOFWHOIS(it->_nick, it->_nick));
            return;
        }        
    }
}
