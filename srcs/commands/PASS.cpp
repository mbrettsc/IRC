#include "../../includes/Server.hpp"

int Server::Pass(std::vector<std::string>& param, Client& client)
{
    if (param.size() == 1 && param[0] == _password)
        client.passcheku = 1;
    return 0;
}
