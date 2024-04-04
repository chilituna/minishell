/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:56:57 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/04 13:04:50 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if readline is NULL, there was error with readline function.
// or the user typed Ctrl+D to exit minishell.
// if readline history exists, it is freed.
void	ft_error_and_exit(char *str, t_data *data)
{
	if (isatty(STDIN_FILENO))
		printf(BLUE1 "%s\n" RESET, str);
	if (history_length > 0)
		rl_clear_history();
	if (data)
		ft_free_data(data);
	if (data->env)
		ft_free_env(data->env);
	free(data);
	exit(1);
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

//error during piping
void	ft_error_piping(t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, STDOUT_FILENO);
	ft_putstr_fd(RED"error in pipe creation"RESET, STDOUT_FILENO);
	data->exit_status = 1;
}

//error during forking
void	ft_error_forking(t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, STDOUT_FILENO);
	ft_putstr_fd(RED"error in fork execution\n"RESET, STDOUT_FILENO);
	data->exit_status = 1;
}

void	ft_error_fd(t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, STDOUT_FILENO);
	ft_putstr_fd(RED"error closing and duplicating file desciptor\n"RESET, STDOUT_FILENO);
	data->exit_status = 1;
}

void	ft_error_executing(t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, STDOUT_FILENO);
	ft_putstr_fd(RED"error with execution\n"RESET, STDOUT_FILENO);
	data->exit_status = 1;
}

void	ft_error_cmd(t_data *data)
{
	ft_putstr_fd(RED"minishell:"RESET, STDERR_FILENO);
	ft_putstr_fd(RED"cannot execute\n"RESET, STDERR_FILENO);
	data->exit_status = 1;
}
