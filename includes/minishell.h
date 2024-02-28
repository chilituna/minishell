/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:08:57 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/28 16:25:28 by aarponen         ###   ########.fr       */
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
# include <limits.h>//to handle PATH_MAX in pwd builtin

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE1 "\033[1;34m"
# define BLUE2 "\033[0;34m"
# define BLUE3 "\033[0;36m"
# define RESET "\033[0m"

//STRUCTS

// Prototype for the main data
typedef struct s_data	t_data;

// Lexer list to store the command line input:
// index of the arg
// str for words
// token for symbols
typedef struct s_lexer
{
	int				index;
	char			*str;
	char			*token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
	t_data			*data;
}	t_lexer;

// Redirection list to store redirections from parser:
typedef struct s_redir
{
	char			*tok;
	char			*filename;
	struct s_redir	*next;
	struct s_redir	*prev;
	t_data			*data;
}	t_redir;

// Command list to store command groups from parser:
// index / total number of commands
// list of tokens from lexer
// command name and flags in cmd_arg
// input and output redirections
// function pointer to the corresponding builtin
typedef struct s_cmd
{
	int				index;
	char			**tokens;
	char			**cmd_arg;
	char			*in;
	char			*out;
	int				(*builtin)(struct s_cmd *cmd);
	struct s_cmd	*next;
	struct s_cmd	*prev;
	t_data			*data;
}	t_cmd;

// Data structure to store the pointers to the lexer, parser and env:
typedef struct s_data
{
	char	*prompt;
	t_lexer	*lexer;
	t_cmd	*cmd;
	char	**env;

}	t_data;

//	- executable (absolute path or in $PATH)
//	- built-in (echo, cd, pwd, export, unset, env, exit)
//	- env variable ($)

//FUNCTIONS

//main.c --> start program, show prompt, loop (TLDR)
int		main(int argc, char **argv, char **envp);
void	ft_print_banner(void);
void	ft_add_env(char **envp, t_data *data);

//error handling
void	ft_error_and_exit(char *str, t_data *data);

//clean_up.c
void	ft_free_data(t_data *data);
void	ft_free_lexer(t_lexer *lexer);
void	ft_free_parser(t_cmd *cmd);

//check quotes
int		ft_check_quotes(char *input);
int		ft_check_doublequotes(char *input);
int		ft_check_singlequotes(char *input);

//utils
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
char	*ft_strdup(const char *s, t_data *data);
char	*ft_substr(char const *s, unsigned int start, size_t len, t_data *data);
int		ft_isspace(int c);
char	*ft_strchr(const char *s, int c);
void	*ft_malloc(size_t size, t_data *data);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);

//lexer.c
t_lexer	*ft_lexer(char *str, t_data *data);
t_lexer	*ft_init_lexer(t_lexer *lexer, int i, t_data *data);
void	ft_tokenizer(t_lexer *lexer);
char	*ft_pick_string(char *str, t_lexer *lexer);
int		ft_quoted_string(char *str, char c);

//parser.c
int		ft_check_pipes(t_lexer *lexer);
t_cmd	*ft_parser(t_lexer *lexer, t_data *data);
t_cmd	*ft_init_cmd(t_cmd *cmd, int i, t_data *data);
t_lexer	*ft_create_cmd(t_lexer *lexer, t_cmd *cmd);
int		ft_count_tokens(t_lexer *lexer);

//check commands
void	ft_check_cmds(t_cmd *cmd);
char	**ft_check_redirections(t_cmd *cmd);
int		ft_is_builtin(char *cmd);
int		(*ft_get_builtin(char *cmd))(t_cmd *cmd);


//builtins
int		ft_echo(t_cmd *cmds);
void	ft_put_line(int n, char **str, int out);
int		ft_pwd(t_cmd *cmds);

//execute
void	ft_execute_cmds(t_cmd *cmd);

#endif

