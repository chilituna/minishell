# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/18 15:53:58 by aarponen          #+#    #+#              #
#    Updated: 2024/03/10 08:49:18 by aarponen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes
LIBS = -lreadline

SRC_DIR = src
SRC_FILES = main.c clean_up.c error_and_exit.c \
	parsing/parser.c parsing/lexer.c parsing/expander.c \
	parsing/check_quotes.c parsing/check_cmds.c parsing/check_builtins.c parsing/check_redirs.c \
	parsing/remove_quotes.c \
	utils/utils.c utils/utils_2.c utils/ft_split.c  utils/utils_3.c utils/ft_itoa.c \
	builtin/ft_echo.c \
	exec/executor.c
OBJ_DIR = obj
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/parsing
	mkdir -p $(OBJ_DIR)/utils
	mkdir -p $(OBJ_DIR)/builtin
	mkdir -p $(OBJ_DIR)/exec

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_FILES) -o $(NAME) $(LIBS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

