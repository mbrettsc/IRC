#include "../../includes/Server.hpp"

int Server::Join(std::vector<std::string>& param, Client& client)
{
    std::string chan = param[0], key = param[1];
    int isThere = 0;
    if (chan.empty())
        Utils::writeMessage(client.cliFd, ERR_NEEDMOREPARAMS);
    if (!client.nick.empty())
    {
        for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
            if (it->getName() == chan)
            {
                if (it->getKey() == "" || it->getKey() == key)
                {
                    it->addClient(client);
                    std::cout << "Client " << client.nick << " has entered this channel" << std::endl;
                }
                else
                    Utils::writeMessage(client.cliFd, ERR_BADCHANNELKEY);
                isThere = 1;
            }
        }
        if (isThere == 0)
        {
            Channel tmp;
            tmp.setName(chan);
            if (!key.empty())
                tmp.setKey(key);
            tmp.setOp();
            _channels.push_back(tmp);
            std::cout << "Channel " << chan << " created with " << key << std::endl;
        }
    }
    else
        Utils::writeMessage(client.cliFd, "Set your nick before!\r\n");
    return 0;
}
