#include "../../includes/Server.hpp"

void Server::Join(std::vector<std::string>& params, Client& cli)
{
    if (cli._passChecked == 0) {
        passChecker(cli);
        return ;
    }
    std::string key = "";
    std::string chan = params[0];
    if (params.size() == 2)
        key = params[1];
    int isThere = 0;
    if (chan.empty()) {
        Utils::writeMessage(cli._cliFd, ERR_NEEDMOREPARAMS(cli._nick, "JOIN"));
        return;
    }
    if (chan[0] != '#' || chan.size() == 1) {
        Utils::writeMessage(cli._cliFd, ERR_INVCHANNAME);
        return;
    }
    if (clientIsInThere(cli, chan) == 0)
    {
        if (!cli._nick.empty())
        {
            for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
                if (it->_name == chan)
                {
                    if (it->_key == key)
                    {
                        if (it->_userLimit != 0 && it->_channelClients.size() >= it->_userLimit)
                        {
                            Utils::writeMessage(cli._cliFd, ERR_CHANNELISFULL(cli._nick, chan));
                            return;
                        }
                        it->_channelClients.push_back(cli);
                        it->_opNick = it->_channelClients[0]._nick;
                        Utils::writeMessage(cli._cliFd, RPL_JOIN(cli._nick, cli._ip, chan));
                        std::cout << PURPLE << "Client " << cli._nick << " has entered \'" << chan << "\'" << RESET << std::endl;
                        showRightGui(cli, *it);
                    }
                    else if (it->_key == "")
                        Utils::writeMessage(cli._cliFd, "Key not required for this channel!\r\n");
                    else
                        Utils::writeMessage(cli._cliFd, ERR_BADCHANNELKEY(cli._nick, chan));
                    isThere = 1;
                }
            }
            if (isThere == 0)
            {
                Channel tmp;
                tmp._name = chan;
                if (!key.empty())
                    tmp._key = key;
                tmp._channelClients.push_back(cli);
                tmp._opNick = tmp._channelClients[0]._nick;
                _channels.push_back(tmp);
                Utils::writeMessage(cli._cliFd, RPL_JOIN(cli._nick, cli._ip, chan));
                if (!key.empty())
                    std::cout << PURPLE << "Channel " << chan << " created with " << key << RESET << std::endl;
                else
                    std::cout << PURPLE << "Channel " << chan << " created" << RESET << std::endl;
                showRightGui(cli, tmp);
            }
        }
        else
            Utils::writeMessage(cli._cliFd, "Set your nick before!\r\n");
    }
    else
        Utils::writeMessage(cli._cliFd, "You are already in this channel\r\n");
}
