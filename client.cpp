#include "socket.hpp"

int main(int ac, char **av)
{
    if (ac == 2)
    {
        Socket clientSock;
        if (connect(clientSock.getFd(), (struct sockaddr *) &clientSock.getAddr(), clientSock.getLen()))
            exit_err("connect");
        send(clientSock.getFd(), av[1], strlen(av[1]), 0);
    }
    return 0;
}