#include "../../includes/Server.hpp"

void Server::Join(std::vector<std::string>& param, Client& client)
{
    passChecker(client);
    std::string chan = param[0], key = param[1];
    int isThere = 0;
    if (chan.empty()) {
        Utils::writeMessage(client.cliFd, ERR_NEEDMOREPARAMS(client.nick, "JOIN"));
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
                        if (it->userLimit != 0 && it->_channelClients.size() >= it->userLimit)
                        {
                            Utils::writeMessage(client.cliFd, ERR_CHANNELISFULL(client.nick, chan));
                            return;
                        }
                        it->_channelClients.push_back(client);
                        it->opNick = it->_channelClients[0].nick;
                        Utils::writeMessage(client.cliFd, RPL_JOIN(client.nick, client.ip, chan));
                        std::cout << "Client " << client.nick << " has entered \'" << chan << "\'" << std::endl;
                        showRightGui(client, *it);
                    }
                    else
                        Utils::writeMessage(client.cliFd, ERR_BADCHANNELKEY(client.nick, chan));
                    isThere = 1;
                }
            }
            if (isThere == 0)
            {
                Channel tmp;
                tmp._name = chan;
                if (!key.empty())
                    tmp._key = key;
                tmp._channelClients.push_back(client);
                tmp.opNick = tmp._channelClients[0].nick;
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
