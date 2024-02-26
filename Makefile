# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luifer <luifer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/18 15:53:58 by aarponen          #+#    #+#              #
#    Updated: 2024/02/26 23:16:04 by luifer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes
LIBS = -lreadline

SRC_DIR = src
SRC_FILES = main.c utils.c utils_2.c check_quotes.c lexer.c parser.c clean_up.c error_and_exit.c ft_echo.c
OBJ_DIR = obj
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_FILES) -o $(NAME) $(LIBS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

