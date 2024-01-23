NAME = ircserv
CC = c++ -std=c++98
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) srcs/*.cpp srcs/commands/*.cpp -o $(NAME) 

bonus: all
	$(CC) $(FLAGS) srcs/bot/*.cpp srcs/Utils.cpp -o bot

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf bot

re: clean all

.PHONY: all clean re bonus
