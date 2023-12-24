#include "../includes/Server.hpp"

int main()
{
    Server *a = Server::getInstance();
    std::cout << a->getFd() << std::endl;
}