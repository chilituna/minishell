/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:08:57 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/25 15:51:07 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //printf, readline functions (readline, rl_clear_history,
	//rl_on_new_line, rl_replace_line, rl_redisplay, add_history,), perror
# include <readline/readline.h> // readline functions
# include <readline/history.h> // readline functions
# include <stdlib.h> //malloc, free, exit, getenv
# include <unistd.h> //write, access, read, close, fork, getcwd, chdir,
	//execve, pipe,dup, dup2, stat, lstat, fstat, unlink, isatty, ttyname,
	//tcsetattr, tcgetattr
# include <sys/types.h> //open, fork, wait, waitpid, wait3, wait4,
	//stat, lstat, fstat, opendir, closedir
# include <sys/stat.h> //open, stat, lstat, fstat
# include <sys/wait.h> //wait, waitpid, wait3, wait4
# include <fcntl.h> //open
# include <signal.h> //signal, sigaction, sigemptyset, sigaddset, kill
# include <string.h> //strerror
# include <dirent.h> //opendir, readdir, closedir
# include <sys/ioctl.h> //ioctl
# include <termios.h> //tcsetattr, tcgetattr
# include <termcap.h> //tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE1 "\033[1;34m"
# define BLUE2 "\033[0;34m"
# define BLUE3 "\033[0;36m"
# define RESET "\033[0m"

//STRUCTS

// Lexer list to store the command line input:
// index of the arg
// str for words
// tok for symbols
typedef struct s_lexer
{
	int				index;
	char			*str;
	char			*token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

// Redirection list to store redirections from parser:
typedef struct s_redir
{
	char			*tok;
	char			*filename;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

// Command list to store command groups from parser:
typedef struct s_cmd
{
	char			*cmd;
	char			**flags;//kind of argv
	char			*in;
	char			*out;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

// Data structure to store everything
typedef struct s_data
{
	t_lexer	*lexer;
	char	**env;
	char	*prompt;
}	t_data;

//	- executable (absolute path or in $PATH)
//	- built-in (echo, cd, pwd, export, unset, env, exit)
//	- env variable ($)

//FUNCTIONS

//main.c --> start program, show prompt, loop (TLDR)
int		main(int argc, char **argv, char **envp);
void	ft_print_banner(void);

//error handling
void	ft_error_and_exit(char *str);

//clean_up.c
void	ft_free_data(t_data *data);
void	ft_free_lexer(t_lexer *lexer);

//check.c
int		ft_check_quotes(char *input);
int		ft_check_doublequotes(char *input);
int		ft_check_singlequotes(char *input);

//utils
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_isspace(int c);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t nmeb, size_t size);

//lexer.c
t_lexer	*ft_lexer(char *str);
t_lexer	*ft_init_lexer(t_lexer *lexer, int i);
void	ft_tokenizer(t_lexer *lexer);
char	*ft_pick_string(char *str, t_lexer *lexer);
int		ft_quoted_string(char *str, char c);

//builtins
int		ft_echo(t_cmd *cmds, t_redir *redir);

#endif

