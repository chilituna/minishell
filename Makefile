# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/18 15:53:58 by aarponen          #+#    #+#              #
#    Updated: 2024/04/20 13:02:59 by aarponen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes
LIBS = -lreadline

SRC_DIR = src
SRC_FILES = main.c signals.c banner.c \
	parsing/parser.c parsing/lexer.c parsing/lexer_helper.c parsing/expander.c \
	parsing/check_quotes.c parsing/check_cmds.c parsing/check_redirs.c \
	parsing/remove_quotes.c parsing/remove_quotes_redir.c \
	utils/utils.c utils/utils_str1.c utils/utils_str2.c utils/utils_env.c utils/utils_env2.c \
	utils/ft_split.c utils/ft_itoa.c \
	utils/utils_lst.c utils/utils_check.c utils/utils_exec.c utils/utils_exec2.c \
	utils/utils_redir.c \
	builtin/ft_echo.c builtin/ft_cd.c builtin/ft_pwd.c builtin/ft_exit.c builtin/ft_env.c \
	builtin/ft_export.c builtin/ft_unset.c \
	exec/executor.c exec/heredoc.c exec/ft_get_path.c exec/execute_builtins.c exec/redirections.c \
	error_and_clean/clean_up.c error_and_clean/clean_up_2.c error_and_clean/error_and_exit.c \
	error_and_clean/error_and_exit_2.c error_and_clean/error_and_exit_3.c
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
	mkdir -p $(OBJ_DIR)/error_and_clean

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_FILES) -o $(NAME) $(LIBS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

