/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarpo e  <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:08:57 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/21 19:17:24 by aarpo e          ###   ########.fr       */
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
	char			*tok;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;


//types of commands:
//	- cmd
//	- flags
//	- in
//	- out

//	- executable (absolute path or in $PATH)
//	- built-in (echo, cd, pwd, export, unset, env, exit)
//	- env variable ($)
//	- tokens:
//	- single quotes '
//	- double quotes "
//	- redirecing output >
//	- redirecing input <
//	- redirecing output in append mode >>
// 	- heredoc <<
//	- pipe |


//FUNCTIONS
//main.c --> start program, show prompt, loop (TLDR)
int		main(void);
void	ft_print_banner(void);

//check.c
int		ft_check_quotes(char *input);

//utils
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);

//lexer.c
t_lexer	*ft_lexer(char **argv);
t_lexer	*ft_init_lexer(t_lexer *lexer, int i);
void	ft_tokenizer(t_lexer *lexer);

#endif

