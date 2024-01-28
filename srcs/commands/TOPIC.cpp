#include "../../includes/Server.hpp"

std::string getTopic(std::vector<std::string>& params)
{
    std::string ret = "";
    if (params[1][0] == ':')
    {
        for (size_t i = 1; i < params.size(); ++i) {
            ret += params[i];
            ret += " ";
        }
    }
    else
        ret = params[1];
    return (ret);
}

void Server::Topic(std::vector<std::string>& params, Client& cli)
{
    passChecker(cli);
    if (params.size() <= 1) {
        Utils::writeMessage(cli._cliFd, ERR_NEEDMOREPARAMS(cli._nick, params[0]));
        return ;
    }
    size_t flag = 0;
    for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
        if (params[0] == it->_name) {
            flag = 1;
            if (params.size() == 1 || params[1] == ":") {
                Utils::writeMessage(cli._cliFd, RPL_NOTOPIC(it->_opNick, params[0]));
                return ;
            }
            else if (params.size() >= 2) {
                if (it->_opNick != cli._nick) {
                    Utils::writeMessage(cli._cliFd, ERR_CHANOPRIVSNEEDED(cli._nick, params[0]));
                    return ;
                }
                it->_topic = getTopic(params);
                std::string top = it->_topic;
                top.erase(0, 1);
                Utils::writeAllMessage(it->getFds(), RPL_TOPIC(cli._nick, cli._ipAddr, params[0], top));
                return ;
            }
        }
    }
    if (flag == 0)
        Utils::writeMessage(cli._cliFd, ERR_NOSUCHCHANNEL(cli._nick, params[0]));
}
