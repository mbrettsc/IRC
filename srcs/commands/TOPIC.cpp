#include "../../includes/Server.hpp"

std::string getTopic(std::vector<std::string>& param)
{
    std::string ret = "";
    if (param[1][0] == ':')
    {
        for (size_t i = 1; i < param.size(); ++i) {
            ret += param[i];
            ret += " ";
        }
        ret.erase(0, 1);
    }
    else
        ret = param[1];
    return (ret);
}

void Server::Topic(std::vector<std::string>& param, Client& cli)
{
    if (param.size() <= 1) {
        Utils::writeMessage(cli.cliFd, ERR_NEEDMOREPARAMS(cli.nick, param[0]));
        return ;
    }
    size_t flag = 0;
    for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
        if (param[0] == it->_name) {
            flag = 1;
            if (param.size() == 1 || param[1] == ":") {
                Utils::writeMessage(cli.cliFd, RPL_NOTOPIC(it->op->nick, param[0]));
                return ;
            }
            else if (param.size() >= 2) {
                if (it->op->nick != cli.nick) {
                    Utils::writeMessage(cli.cliFd, ERR_CHANOPRIVSNEEDED(cli.nick, param[0]));
                    return ;
                }
                it->_topic = param[1];
                Utils::writeAllMessage(it->getFds(), RPL_TOPIC(cli.nick, cli.ipAddr, param[0], getTopic(param).c_str()));
                return ;
            }
        }
    }
    if (flag == 0)
        Utils::writeMessage(cli.cliFd, ERR_NOSUCHCHANNEL(cli.nick, param[0]));
}
