/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:56:57 by aarponen          #+#    #+#             */
/*   Updated: 2024/06/01 14:08:23 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if readline is NULL, there was error with readline function.
// or the user typed Ctrl+D to exit minishell.
// if readline history exists, it is freed.
void	ft_error_and_exit(char *str, t_data *data)
{
	int	exit_status;

	if (isatty(STDIN_FILENO))
		printf(BLUE1 "%s\n" RESET, str);
	if (history_length > 0)
		rl_clear_history();
	if (data)
		ft_free_data(data);
	if (data->env)
		ft_free_env(data->env);
	if (g_signal_nr == -1)
		exit_status = data->exit_status;
	else
		exit_status = 128 + g_signal_nr;
	free(data);
	ft_print_exit();
	exit(exit_status);
}

// error for incorrect number of arguments when launching the program
void	ft_error_minishell(char *str)
{
	printf(RED "ERROR: %s\n" RESET, str);
	exit(1);
}

// exit minishell
void	ft_exit_minishell(t_data *data)
{
	int	exit_status;

	if (history_length > 0)
		rl_clear_history();
	if (data)
		ft_free_data(data);
	if (data->env)
		ft_free_env(data->env);
	exit_status = data->exit_status;
	free(data);
	exit(exit_status);
}

int	ft_print_error(char *error)
{
	printf(RED "%s\n" RESET, error);
	return (0);
}

// error for heredoc signal: ctrl+D
int	ft_heredoc_error(t_data *data)
{
	ft_putstr_fd(RED"minishell: warning: "RESET, STDOUT_FILENO);
	ft_putstr_fd(RED"heredoc received end of file\n"RESET, STDOUT_FILENO);
	data->exit_status = 1;
	return (1);
}
