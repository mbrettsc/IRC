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
    message += "|   - Martin Burak Brettschneider (mbrettsc)               |\n";
    message += "|   - Umut Akkan                  (uakkan)                 |\n";
    message += "|   - Yiğithan Karabulut          (ykarabul)               |\n";
    message += "|                                                          |\n";
    message += "| * Current commands:                                      |\n";
    message += "|   - BOT                                                  |\n";
    message += "|   - CAP                                                  |\n";
    message += "|   - HELPME                                               |\n";
    message += "|   - INFO                                                 |\n";
    message += "|   - INVITE                                               |\n";
    message += "|   - JOIN                                                 |\n";
    message += "|   - KICK                                                 |\n";
    message += "|   - LIST                                                 |\n";
    message += "|   - MODE                                                 |\n";
    message += "|   - NICK                                                 |\n";
    message += "|   - NOTICE                                               |\n";
    message += "|   - OPER                                                 |\n";
    message += "|   - PART                                                 |\n";
    message += "|   - PASS                                                 |\n";
    message += "|   - PRIVMSG                                              |\n";
    message += "|   - QUIT                                                 |\n";
    message += "|   - TOPIC                                                |\n";
    message += "|   - USER                                                 |\n";
    message += "|   - WHO                                                  |\n";
    message += "|   - WHOIS                                                |\n";
    message += " +--------------------------------------------------------+\n";
    return (message);
}

void Server::Info(std::vector<std::string>& params, Client &cli)
{
    passChecker(cli);
    (void)params;
    Utils::writeMessage(cli._cliFd, RPL_INFO(cli._nick, infoMessage()));
}
