#include "../../includes/Server.hpp"
#include <algorithm>

void Server::Mode(std::vector<std::string>& param, Client& cli)
{
    for (size_t i = 0; i < param.size(); ++i)
        std::cout << "param[" << i << "] = " << param[i] << std::endl;
    if (cli.isCap == NC)
        passChecker(cli);
    if (param.size() == 1)
        return;
    if (param.size() < 1 || param.size() > 3) {
        Utils::writeMessage(cli.cliFd, ERR_NEEDMOREPARAMS(cli.nick, param[0]));
        return ;
    }
    if (param.size() == 1)
        return;
    if (!isChannelExist(param[0])) {
        Utils::writeMessage(cli.cliFd, ERR_NOSUCHCHANNEL(cli.nick, param[0]));
        return;
    }
    for (chanIt it = _channels.begin(); it != _channels.end(); ++it) {
        if (it->_name == param[0])
        {
            if (it->opNick != cli.nick) {
                Utils::writeMessage(cli.cliFd, ERR_CHANOPRIVSNEEDED(cli.nick, param[0]));
                return ;
            }
            int flag = 0;
            modesOp(it, param, &flag);
            modesLimit(it, param, &flag);
            modesKey(it, param, &flag);
            if (!flag) {
                Utils::writeMessage(cli.cliFd, "No such mode\r\n");
                return ;
            }
        }
    }
}

void Server::modesOp(chanIt& it, std::vector<std::string>& param, int* flag)
{
    if (param[1] == "+o")
    {
        *flag = 1;
        size_t flag2 = 0;
        for (cliIt it2 = it->_channelClients.begin(); it2 != it->_channelClients.end(); ++it2) {
            if (it2->nick == param[2])
            {
                if (it2->nick == it->opNick) {
                    Utils::writeMessage(getOpFd(it->opNick), "You are already operator\r\n");
                    return ;
                }
                flag2 = 1;
                size_t i;
                for (i = 0; i < it->_channelClients.size(); ++i) {
                    if (it->_channelClients[i].nick == it2->nick)
                        break ;
                }
                Client tmp = it->_channelClients[i];
                it->_channelClients[i] = it->_channelClients[0];
                it->_channelClients[0] = tmp;
                it->opNick = it->_channelClients[0].nick;
                showRightGui(tmp, *it);
                return ;
            }
        }
        if (flag2 == 0) 
        {
            Utils::writeMessage(getOpFd(it->opNick), "User is not in the channel\r\n");
            return ;
        }
    }
}

void Server::modesLimit(chanIt& it, std::vector<std::string>& param, int* flag)
{
    for (size_t i = 0; i < param.size(); ++i)
        std::cout << "param[" << i << "] = " << param[i] << std::endl;
    if (param[1] != "+l" && param[1] != "-l")
        return ;
    *flag = 1;
    if (param[1] == "-l")
        it->userLimit = 0;
    if (param[1] == "+l")
        it->userLimit = std::stoi(param[2]);
    Utils::writeMessage(getOpFd(it->opNick), RPL_MODE(it->opNick, param[0], "+l", param[2]));
    return ;
}

void Server::modesKey(chanIt& it, std::vector<std::string>& param, int* flag)
{
    if (param[1] != "+k" && param[1] != "-k")
        return ;
    if (param[1] == "+k" && param.size() != 3)
        return ;
    if(param[1] == "+k")
        it->_key = param[2];
    else if (param[1] == "-k")
        it->_key = "";
    *flag = 1;
}

// MODE #<channel name> +l 20   -----> (max user count)
// mode #<channel name> +k 123  -----> (sifre 123 oldu.)
// mode #channel name > -k 
// void Server::modesBanned(chanIt& it, std::vector<std::string>& param, int* flag)
// {
//     (void)it;
//     if (param[1] != "+b" && param[1] != "-b")
//         return ;
//     if (param[1] == "-b" && param.size() != 3)
//         return ;
//     if (param[1] == "+b")
//     {
//         if (param.size() == 3)
//         {
//             if (!isNickExist(param[2]))
//                 return ;
//             it->_bannedClients.push_back(param[2]);
//         }
        
//         Utils::writeMessage(it->op->cliFd, RPL_MODE(it->opNick, param[0], "+b", param[2]));
//         // TODO: iteratorle don banned list _bannedClients
//     }
//     else if (param[1] == "-b" && param.size() == 3)
//     {
//         if (!isNickExist(param[2]))
//             return ;
//         std::vector<std::string>::iterator it2 = find(it->_bannedClients.begin(), it->_bannedClients.end(), param[2]);
//         it->_bannedClients.erase(it2);
//     }
//     *flag = 1;
// }
