#include "../../includes/Server.hpp"

void Server::Mode(std::vector<std::string>& param, Client& cli)
{
    for (std::vector<std::string>::iterator it = param.begin(); it != param.end(); ++it)
        std::cout << *it << std::endl;
    std::cout << "---------\n";
    if (cli.isCap == NC)
        passChecker(cli);
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
            if (it->op->nick != cli.nick) {
                Utils::writeMessage(cli.cliFd, ERR_CHANOPRIVSNEEDED(cli.nick, param[0]));
                return ;
            }
            int flag = 0;
            modesBanned(it, param, &flag);
            modesLimit(it, param, &flag);
            modesKey(it, param, &flag);
            if (!flag) {
                Utils::writeMessage(cli.cliFd, "SEKTER GET fuck you motherfucker nigga bitch");
                return ;
            }
            std::cout << it->userLimit << std::endl;
            
        }
    }
}

#include <algorithm>

void Server::modesBanned(chanIt& it, std::vector<std::string>& param, int* flag)
{
    (void)it;
    if (param[1] != "+b" && param[1] != "-b")
        return ;
    if (param[1] == "-b" && param.size() != 3)
        return ;
    if (param[1] == "+b")
    {
        if (param.size() == 3)
        {
            if (!isNickExist(param[2]))
                return ;
            it->_bannedClients.push_back(param[2]);
        }
        
        Utils::writeMessage(it->op->cliFd, RPL_MODE(it->op->nick, param[0], "+b", param[2]));
        // TODO: iteratorle don banned list _bannedClients
    }
    else if (param[1] == "-b" && param.size() == 3)
    {
        if (!isNickExist(param[2]))
            return ;
        std::vector<std::string>::iterator it2 = find(it->_bannedClients.begin(), it->_bannedClients.end(), param[2]);
        it->_bannedClients.erase(it2);
    }
    *flag = 1;
}

// mode #a +b                      -----> (banlananlar listelendi)
// mode #a +b kirve                -----> (kirve banlandi)
// mode #a -b kirve 

void Server::modesLimit(chanIt& it, std::vector<std::string>& param, int* flag)
{
    if (param[1] != "+l" && param[1] != "-l")
        return ;
    *flag = 1;
    std::stringstream ss(param[2]);
    int n; ss >> n;
    if (param[1] == "-l")
        it->userLimit = 0;
    if (param[1] == "+l")
        it->userLimit = n;
    Utils::writeMessage(it->op->cliFd, RPL_MODE(it->op->nick, param[0], "+l", param[2]));
    return ;
}

void Server::modesKey(chanIt& it, std::vector<std::string>& param, int* flag)
{
    if (param[1] != "+k" && param[1] != "-k")
        return ;
    if (param[1] == "+k" && param.size() != 3)
        return ;
    if (param[1] == "-k" && param.size() != 2)
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
// kanka irc iste sohbet ediyoruz amk
