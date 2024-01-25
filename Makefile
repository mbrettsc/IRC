NAME = ircserv
CC = c++
CFLAGS = -std=c++98 -Wall -Wextra -Werror
SRC_DIR = srcs
OBJ_DIR = obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/commands/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(dir $(OBJ_FILES))

bonus:
	$(CC) $(CFLAGS) $(SRC_DIR)/bot/*.cpp $(SRC_DIR)/Utils.cpp $^ -o bot

clean:
	rm -rf $(NAME) bot

fclean: clean
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
