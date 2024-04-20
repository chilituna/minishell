/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:50:14 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/20 14:56:24 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//interrupt the command and display a new prompt on a new line
void	ft_interrupt(int signal)
{
	if (signal == SIGQUIT)
	{
		ft_putstr_fd(RED"Quit (core dumped)\n"RESET, STDERR_FILENO);
		g_exit_signals = 131;
	}
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_exit_signals = 130;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
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
	g_exit_signals = 130;
}

void	ft_heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// ctrl-C displays a new prompt on a new line (SIGINT)
// ctrl-D exits the shell. -- taken care within readline.
// ctrl-\ does nothing (SIGQUIT)
void	ft_signals_interactive(void)
{
	signal(SIGINT, ft_new_prompt);
	signal(SIGQUIT, SIG_IGN);
}

// ctrl-C: Interrupts the current command and
// displays a new prompt on a new line.
// TODO: ctrl-D: In the context of a here document (heredoc),
// it typically marks the end-of-file (EOF),
// signaling to the shell that the input is complete.
// ctrl-\: Exits the shell abruptly by sending a SIGQUIT signal.
void	ft_signals_running(void)
{
	signal(SIGINT, ft_interrupt);
	signal(SIGQUIT, ft_interrupt);
}

void	ft_signals_heredoc(void)
{
	signal(SIGINT, ft_heredoc_handler);
}

