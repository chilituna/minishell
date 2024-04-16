/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:50:14 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/16 15:40:26 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//interrupt the command and display a new prompt on a new line
void	ft_interrupt(int signal)
{
	if (signal == SIGQUIT)
		printf("Quit (core dumped)\n");
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// Signal handler for SIGINT (Ctrl-C)
// When the user presses Ctrl-C, the signal is sent to the process
// and the handler is called. The handler writes a newline character
// to the standard output, replaces the current line with an empty
// string, moves the cursor to the beginning of the line and redisplays
// the prompt.
void	ft_new_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// ctrl-C displays a new prompt on a new line (SIGINT)
// ctrl-D exits the shell. -- taken care within readline.
// ctrl-\ does nothing (SIGQUIT)
void	ft_signals_interactive(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	memset(&sa_int, 0, sizeof(sa_int));
	signal(SIGINT, ft_new_prompt);
	//sa_int.sa_handler = &ft_new_prompt;
	//sigaction(SIGINT, &sa_int, NULL);
	memset(&sa_quit, 0, sizeof(sa_quit));
	signal(SIGQUIT, SIG_IGN);
	//sa_quit.sa_handler = SIG_IGN;
	//sigaction(SIGQUIT, &sa_quit, NULL);
}

// ctrl-C: Interrupts the current command and
// displays a new prompt on a new line.
// TODO: ctrl-D: In the context of a here document (heredoc),
// it typically marks the end-of-file (EOF),
// signaling to the shell that the input is complete.
// ctrl-\: Exits the shell abruptly by sending a SIGQUIT signal.
void	ft_signals_running(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	memset(&sa_int, 0, sizeof(sa_int));
	signal(SIGINT, ft_interrupt);
	//sa_int.sa_handler = &ft_interrupt;
	//sigaction(SIGINT, &sa_int, NULL);
	memset(&sa_quit, 0, sizeof(sa_quit));
	signal(SIGQUIT, ft_interrupt);
	//sa_quit.sa_handler = &ft_interrupt;
	//sigaction(SIGQUIT, &sa_quit, NULL);
}

/*
void	ft_reset_prompt(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

void	ft_new_line(int signum)
{
	if (signum == SIGQUIT)
		ft_putstr_fd(RED"Quit (core dumped)\n"RESET, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
}

void	ft_signals_interactive(void)
{
	signal(SIGINT, ft_reset_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signals_non_interactive(void)
{
	signal(SIGINT, ft_new_line);
	signal(SIGQUIT, ft_new_line);
}
*/



