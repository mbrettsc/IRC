#include "../includes/Server.hpp"

int Server::isNickExist(std::string const& nick)
{
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->_nick == nick)
            return 1;
    }
    return 0;
}

void Server::kickClient(cliIt& it)
{
    std::cout << RED << "Client " << it->_cliFd - 3  << " disconnected!" << RESET << std::endl;
    FD_CLR(it->_cliFd, &_readFds);
    FD_CLR(it->_cliFd, &_writeFds);
    close(it->_cliFd);
    _clients.erase(it);
}

void Server::passChecker(Client& client)
{
    if (client._passChecked == 0)
    {
        std::cout << RED << client._cliFd - 3 << " is not logged in. Tschüss!" << RESET << std::endl;
        for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
            if (client._cliFd == it->_cliFd)
            {
                Utils::writeMessage(client._cliFd, ERR_PASSWDMISMATCH);
                kickClient(it);
                break;
            }
        }
    }
}

void Server::getAfterColon(std::vector<std::string>& params)
{
    params[1].erase(0, 1);
    for (size_t i = 2; i < params.size(); ++i) {
        params[1] += " " + params[i];
    }
}

Channel& Server::getChannel(std::string const& channelName)
{
    chanIt it;
    for (it = _channels.begin(); it != _channels.end(); ++it) {
        if (it->_name == channelName) {
            break;
        }
    }
    return *it;
}

int Server::isChannelExist(std::string const& channelName)
{
    for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
        if (it->_name == channelName)
            return 1;
    }
    return 0;
}

int Server::clientIsInThere(Client& client, std::string const& chanName)
{
    for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
        if (it->_name == chanName)
        {
            for (cliIt it2 = it->_channelClients.begin(); it2 != it->_channelClients.end(); ++it2) {
                if (it2->_nick == client._nick)
                    return (1);
            }
        }
    }
    return (0);
}

int Server::getOpFd(std::string const& opName)
{
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->_nick == opName)
            return (it->_cliFd);
    }
    return (0);
}

void Server::showRightGui(Client &cli, Channel &tmp) {
    std::string msg;
    if (tmp._name.empty())
        return;
    for(std::vector<Client>::iterator it = tmp._channelClients.begin() ; it != tmp._channelClients.end(); ++it) {
        if (it->_cliFd == getOpFd(tmp._opNick))
            msg += "@";
        msg += (*it)._nick + " ";
    }
    Utils::writeAllMessage(tmp.getFds(), RPL_NAMREPLY(cli._nick, tmp._name, msg));
    Utils::writeAllMessage(tmp.getFds(), RPL_ENDOFNAMES(cli._nick, tmp._name));
}

void Server::setPort(size_t const& port)
{
    _port = port;
}

void Server::setPassword(std::string const& password)
{
    _password = password;
}

void Server::printStatus()
{
    char name[255];

    gethostname(name, sizeof(name));
    std::cout << CYAN << "Server running on: " << name << RESET << std::endl;
    std::cout << CYAN <<"Password: " << _password << RESET << std::endl;
    std::cout << CYAN << "Port: " << _port << RESET << std::endl;
}
