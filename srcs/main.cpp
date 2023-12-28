#include "../includes/Server.hpp"

int main(int ac, char **av)
{
    if (ac == 3 && Server::portIsValid(av[1]))
        Server::getInstance()->manageServer(atoi(av[1]), av[2]);
    else
        std::cout << "this program takes 2 arguments" << std::endl;
    return 0;
}