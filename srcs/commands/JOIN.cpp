#include "../../includes/Server.hpp"

int Server::clientIsInThere(Client& client, std::string const& chanName)
{
    for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
        if (it->_name == chanName)
        {
            for (cliIt it2 = it->_channelClients.begin(); it2 != it->_channelClients.end(); ++it2) {
                if (it2->nick == client.nick)
                    return (1);
            }
        }
    }
    return (0);
}

void Server::showRightGui(Client &cli, Channel &tmp) {
    std::string msg;
    if (tmp._name.empty())
        return;
    for(std::vector<Client>::iterator it = tmp._channelClients.begin() ; it != tmp._channelClients.end(); ++it) {
        if (it->cliFd == tmp.op->cliFd)
            msg += "@";
        msg += (*it).nick + " ";
    }
    Utils::writeAllMessage(tmp.getFds(), RPL_NAMREPLY(cli.nick, tmp._name, msg));
    Utils::writeAllMessage(tmp.getFds(), RPL_ENDOFNAMES(cli.nick, tmp._name));
}

void Server::Join(std::vector<std::string>& param, Client& client)
{
    passChecker(client);
    std::string chan = param[0], key = param[1];
    int isThere = 0;
    if (chan.empty()) {
        Utils::writeMessage(client.cliFd, ERR_NEEDMOREPARAMS);
        return;
    }
    if (chan[0] != '#') {
        Utils::writeMessage(client.cliFd, ERR_INVCHANNAME);
        return;
    }
    if (clientIsInThere(client, chan) == 0)
    {
        if (!client.nick.empty())
        {
            for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
                if (it->_name == chan)
                {
                    if (it->_key == "" || it->_key == key)
                    {
                        it->_channelClients.push_back(client);
                        it->op = &it->_channelClients[0];
                        Utils::writeMessage(client.cliFd, RPL_JOIN(client.nick, client.ip, chan));
                        std::cout << "Client " << client.nick << " has entered \'" << chan << "\'" << std::endl;
                        showRightGui(client, *it);
                    }
                    else
                        Utils::writeMessage(client.cliFd, ERR_BADCHANNELKEY);
                    isThere = 1;
                }
            }
            if (isThere == 0)
            {
                Channel tmp;
                tmp._name = chan;
                std::cout << key << std::endl << !key.empty() << std::endl;
                if (!key.empty())
                    tmp._key = key;
                tmp.op = &client;
                tmp._channelClients.push_back(client);
                _channels.push_back(tmp);
                Utils::writeMessage(client.cliFd, RPL_JOIN(client.nick, client.ip, chan));
                if (!key.empty())
                    std::cout << "Channel " << chan << " created with " << key << std::endl;
                else
                    std::cout << "Channel " << chan << " created" << std::endl;
                showRightGui(client, tmp);
            }
        }
        else
            Utils::writeMessage(client.cliFd, "Set your nick before!\r\n");
    }
    else
        Utils::writeMessage(client.cliFd, "You are already in this channel\r\n");
}
