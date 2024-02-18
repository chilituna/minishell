/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:08:57 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/18 18:16:10 by aarponen         ###   ########.fr       */
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

//FUNCTIONS
//main.c --> start program, show prompt, loop (TLDR)
int		main(void);
void	ft_print_banner(void);

#endif

