/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:50:14 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/21 14:47:47 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//interrupt the command and display a new prompt on a new line
void	ft_interrupt(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd(RED"Quit (core dumped)\n"RESET, STDERR_FILENO);
	if (signal == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
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
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	if (signal == SIGINT)
		g_signal_nr = signal;
}

void	ft_heredoc_handler(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_replace_line("", 0);
	g_signal_nr = signal;
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
