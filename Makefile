NAME = ircserv
CC = c++ -std=c++98
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) srcs/*.cpp -o $(NAME) 

clean:
	rm -rf $(NAME)

re: clean all

.PHONY: all clean re
