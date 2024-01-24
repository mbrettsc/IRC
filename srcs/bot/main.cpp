#include "../../includes/Bot.hpp"

int main(int ac, char **av)
{
    try {
        if (ac != 3)
            throw std::runtime_error("./bot <port> <password>");
        if (!Utils::portIsValid(av[1]))
            throw std::runtime_error("invalid port");
        Bot::getInstance()->manageBot(atoi(av[1]), av[2]);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
