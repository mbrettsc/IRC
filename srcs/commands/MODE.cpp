#include "../../includes/Server.hpp"

void Server::Mode(std::vector<std::string>& param, Client& cli)
{
    if (cli.isCap == NC)
        passChecker(cli);
    if (param.size() == 1)
        return ;
    if (param.size() > 3)
        Utils::writeMessage(cli.cliFd, ERR_NEEDMOREPARAMS);
    // else if (param[0] == cli.nick) {
    //     if (param[1] == "+i")
    //         cli.isInvisible = 1;
    //     else if (param[1] == "-i")
    //         cli.isInvisible = 0;
    //     else if (param[1] == "+w")
    //         cli.isWallops = 1;
    //     else if (param[1] == "-w")
    //         cli.isWallops = 0;
    //     else if (param[1] == "+o")
    //         cli.isOperator = 1;
    //     else if (param[1] == "-o")
    //         cli.isOperator = 0;
    //     else if (param[1] == "+s")
    //         cli.isServerNotices = 1;
    //     else if (param[1] == "-s")
    //         cli.isServerNotices = 0;
    //     else if (param[1] == "+a")
    //         cli.isAway = 1;
    //     else if (param[1] == "-a")
    //         cli.isAway = 0;
    //     else if (param[1] == "+r")
    //         cli.isRestricted = 1;
    //     else if (param[1] == "-r")
    //         cli.isRestricted = 0;
    //     else if (param[1] == "+x")
    //         cli.isCloaked = 1;
    //     else if (param[1] == "-x")
    //         cli.isCloaked = 0;
    //     else if (param[1] == "+n")
    //         cli.isRegistered = 1;
    //     else if (param[1] == "-n")
    //         cli.isRegistered = 0;
    //     else if (param[1] == "+g")
    //         cli.isRegistered = 1;
    //     else if (param[1] == "-g")
    //         cli.isRegistered = 0;
    //     else if (param[1] == "+k")
    //         cli.isRegistered = 1;
    //     else if (param[1] == "-k")
    //         cli.isRegistered = 0;
    //     else if (param[1] == "+u")
    //         cli.isRegistered = 1;
    //     else if (param[1] == "-u")
    //         cli.isRegistered
    // }
}