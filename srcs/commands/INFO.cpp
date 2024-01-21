#include "../../includes/Server.hpp"

std::string infoMessage()
{
    std::string message;

    message += " +--------------------------------------------------------+\n";
    message += "| * Based on the original code written by Jarkko Oikarinen |\n";
    message += "| * Copyright 1988, 1989, 1990, 1991 University of Oulu,   |\n";
    message += "|   Computing Center                                       |\n";
    message += "|                                                          |\n";
    message += "| * This program is free software; you can redistribute it |\n";
    message += "|   and/or modify it under the terms of the MIT License as |\n";
    message += "|   published by the Free Software Foundation; either      |\n";
    message += "|   version 1, or (at your option) any later version.      |\n";
    message += "|                                                          |\n";
    message += "| * Developers:                                            |\n";
    message += "|   - Martin Burak Brettschneider                          |\n";
    message += "|   - Umut Akkan                                           |\n";
    message += "|   - Yiğithan Karabulut                                   |\n";
    message += "|                                                          |\n";
    message += "| * Current commands:                                      |\n";
    message += "|   - CAP                                                  |\n";
    message += "|   - INFO                                                 |\n";
    message += "|   - JOIN                                                 |\n";
    message += "|   - MODE                                                 |\n";
    message += "|   - NICK                                                 |\n";
    message += "|   - PART                                                 |\n";
    message += "|   - PASS                                                 |\n";
    message += "|   - PRIVMSG                                              |\n";
    message += "|   - QUIT                                                 |\n";
    message += "|   - USER                                                 |\n";
    message += "|   - WHO                                                  |\n";
    message += " +--------------------------------------------------------+\n";
    return (message);
}

void Server::Info(std::vector<std::string>& x, Client &client)
{
    passChecker(client);
    (void)x;
    Utils::writeMessage(client.cliFd, RPL_INFO(client.nick, infoMessage()));
}
