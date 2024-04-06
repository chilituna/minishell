/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:16:10 by luifer            #+#    #+#             */
/*   Updated: 2024/04/05 11:42:01 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

//function for error in duplicating file descriptor
void	ft_error_dup(t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, STDOUT_FILENO);
	ft_putstr_fd(RED"error closing and duplicating file desciptor\n"RESET, STDOUT_FILENO);
	data->exit_status = 1;
}

void	ft_error_closing(t_data *data)
{
	ft_putstr_fd(RED"minishell:"RESET, STDOUT_FILENO);
	ft_putstr_fd(RED"error closing fd:"RESET, STDOUT_FILENO);
	data->exit_status = 1;
}

void	ft_error_executing(t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, STDOUT_FILENO);
	ft_putstr_fd(RED"error: cannot execute\n"RESET, STDOUT_FILENO);
	data->exit_status = 1;
}

void	ft_error_cmd(t_data *data)
{
	ft_putstr_fd(RED"minishell:"RESET, STDERR_FILENO);
	ft_putstr_fd(RED"cannot execute\n"RESET, STDERR_FILENO);
	data->exit_status = 1;
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