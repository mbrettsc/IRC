#  FT_IRC

This project is an implementation of an Internet Relay Chat (IRC) server, following the specifications outlined in RFC 1459. IRC is a widely used protocol for real-time communication in the form of text messages between users in a network of servers. RFC 1459 defines the standards for IRC, covering various aspects such as message formats, server-client communication, channel management, and user authentication.

##  Table of Contents

-  [Developers](#developers)

-  [Usage](#usage)

-  [Commands](#commands)

-  [License](#license)

## Developers

[![-----------------------------------------------------](
https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)](https://github.com/mbrettsc)

<div align="center">
<table>
  <tbody>
    <tr>
      <td  align="center"  valign="top"  width="20%"><a  href="https://github.com/mbrettsc"><img  src="https://avatars.githubusercontent.com/u/99292553?v=4"  width="100px;"  alt="Martin Burak Brettschneider"/><br  /><sub><b>Martin Burak Brettschneider</b></sub></a><br  /></td>
      <td  align="center"  valign="top"  width="20%"><a  href="https://github.com/yigithankarabulut"><img  src="https://avatars.githubusercontent.com/u/120645917?v=4"  width="100px;"  alt="Yiğithan Karabulut"/><br  /><sub><b>Yiğithan Karabulut</b></sub></a><br  /></td>
      <td  align="center"  valign="top"  width="20%"><a  href="https://github.com/umuttakkan"><img  src="https://avatars.githubusercontent.com/u/91291348?v=4"  width="100px;"  alt="Umut Akkan"/><br  /><sub><b>Umut Akkan</b></sub></a><br  /></td>
</td>
    </tr>
  </table>
</tbody>
</div>
   
[![-----------------------------------------------------](
https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)](https://github.com/mbrettsc)

## Usage

###  Hexchat

-  After installing Hexchat, in the "Network List" window, click the "Add" button to add a new server.

-  Enter the server name, edit the address and port for your IRC server.

-  In the "Login Method" field, select the Server Password command (/PASS password).

###  Netcat (nc)

-  nc "hostname" "port".

-  Then you can see how to enter the server with "HELPME" command.  

##  Commands

-  **BOT**: If the bot is connected to the server, it will broadcast a message to all clients, and the content of this message will be based on the first parameter provided.

-  **CAP**: The CAP command serves as a handshake mechanism between server to HexChat and bot.

-  **HELPME**: The HELPME command provides users with explanations on how to connect to the server using Netcat. It is a helpful resource for users who may be new to the IRC environment or need assistance with the connection process.

-  **INFO**: The INFO command lists all available commands, serving as a quick reference guide for users to understand the functionalities offered by the IRC system.

-  **INVITE**: The INVITE command is used by operators to invite someone to a specific channel, granting them access to the channel's conversations and activities.

-  **JOIN**: The JOIN command allows users to either create a new channel or join an existing one, enabling them to participate in discussions within that channel.

-  **KICK**: The KICK command is a tool for channel operators to remove a user from a channel, maintaining control over the channel environment.

-  **LIST**: The LIST command provides a list of all channels along with their respective topics, offering users an overview of the available channels on the server.

-  **MODE**: Only operators use the MODE command, and it is related to channel settings. Operators can modify channel parameters, such as changing the channel's key or setting user limits.

-  **NICK**: The NICK command allows users to set or change their nickname, providing a personalized identifier for interactions on the IRC network.

-  **NOTICE**: The NOTICE command is used to send messages to clients, providing a means of communication between users without broadcasting the message to an entire channel.

-  **OPER**: The OPER command allows operators to grant operator privileges to another user, expanding the team of individuals with administrative control over the channel.

-  **PART**: The PART command is used to leave a specific channel, allowing users to exit channels they no longer wish to participate in.

-  **PASS**: The PASS command is used to enter the server password, ensuring secure access to the IRC network.

-  **PRIVMSG**: The PRIVMSG command allows users to send private messages to specific clients or broadcast messages to an entire channel

-  **QUIT**: The QUIT command is used to gracefully exit the server, signaling the end of a user's connection.

-  **TOPIC**: The TOPIC command enables users to set the topic for a specific channel, providing a brief description or focus for discussions within that channel.

-  **USER**: The USER command is used to set or change the username associated with a user's connection.

-  **WHO**: The WHO command lists all users in a specific channel, offering a snapshot of the current participants in that channel.

-  **WHOIS**: The WHOIS command prints detailed information about a specific user, providing insights into their connection details and other relevant information. 

##  License

[MIT License](LICENSE)
