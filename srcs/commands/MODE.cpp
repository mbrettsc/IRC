#include "../../includes/Server.hpp"
#include <algorithm>

void Server::Mode(std::vector<std::string>& params, Client& cli)
{
    passChecker(cli);
    if (params.size() == 1)
        return;
    if (params.size() < 1 || params.size() > 3) {
        Utils::writeMessage(cli._cliFd, ERR_NEEDMOREPARAMS(cli._nick, params[0]));
        return ;
    }
    if (params.size() == 1)
        return;
    if (!isChannelExist(params[0])) {
        Utils::writeMessage(cli._cliFd, ERR_NOSUCHCHANNEL(cli._nick, params[0]));
        return;
    }
    for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
        if (it->_name == params[0])
        {
            if (it->_opNick != cli._nick) {
                Utils::writeMessage(cli._cliFd, ERR_CHANOPRIVSNEEDED(cli._nick, params[0]));
                return ;
            }
            int flag = 0;
            modesOp(it, params, &flag);
            modesLimit(it, params, &flag);
            modesKey(it, params, &flag);
            if (!flag) {
                Utils::writeMessage(cli._cliFd, ERR_UNKNOWNMODE(cli._nick, params[0], params[1]));
                return ;
            }
        }
    }
}

void Server::modesOp(chanIt& it, std::vector<std::string>& params, int* flag)
{
    if (params[1] == "+o")
    {
        *flag = 1;
        size_t flag2 = 0;
        for (cliIt it2 = it->_channelClients.begin(); it2 != it->_channelClients.end(); ++it2) {
            if (it2->_nick == params[2])
            {
                if (it2->_nick == it->_opNick)
                    return ;
                flag2 = 1;
                size_t i;
                for (i = 0; i < it->_channelClients.size(); ++i) {
                    if (it->_channelClients[i]._nick == it2->_nick)
                        break ;
                }
                Client tmp = it->_channelClients[i];
                it->_channelClients[i] = it->_channelClients[0];
                it->_channelClients[0] = tmp;
                it->_opNick = it->_channelClients[0]._nick;
                showRightGui(tmp, *it);
                return ;
            }
        }
        if (flag2 == 0) 
        {
            Utils::writeMessage(getOpFd(it->_opNick), "User is not in the channel\r\n");
            return ;
        }
    }
}

void Server::modesLimit(chanIt& it, std::vector<std::string>& params, int* flag)
{
    if (params[1] != "+l" && params[1] != "-l")
        return ;
    *flag = 1;
    if (params[1] == "-l")
        it->_userLimit = 0;
    if (params[1] == "+l")
        it->_userLimit = std::stoi(params[2]);
    Utils::writeMessage(getOpFd(it->_opNick), RPL_MODE(it->_opNick, params[0], "+l", params[2]));
    return ;
}

void Server::modesKey(chanIt& it, std::vector<std::string>& params, int* flag)
{
    if (params[1] != "+k" && params[1] != "-k")
        return ;
    if (params[1] == "+k" && params.size() != 3)
        return ;
    if(params[1] == "+k")
        it->_key = params[2];
    else if (params[1] == "-k")
        it->_key = "";
    *flag = 1;
}
