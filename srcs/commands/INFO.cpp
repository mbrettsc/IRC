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
    message += "|                                                          |\n";
    message += "| * Project Information:                                   |\n";
    message += "|   - Start Date: Unknown                                  |\n";
    message += "|   - Finish Date: 1459                                    |\n";
    message += " +--------------------------------------------------------+\n";
    return (message);
}

void Server::Info(std::vector<std::string>& x, Client &client)
{
    (void)x;
    Utils::writeMessage(client.cliFd, infoMessage());
}
