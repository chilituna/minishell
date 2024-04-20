/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:16:10 by luifer            #+#    #+#             */
/*   Updated: 2024/04/20 18:39:29 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function for error in duplicating file descriptor
int	ft_error_dup(t_data *data)
{
	ft_putstr_fd(RED"minishell: ", STDERR_FILENO);
	ft_putstr_fd("error duplicating file desciptor\n"RESET, STDERR_FILENO);
	data->exit_status = 1;
	return (1);
}

int	ft_error_executing(t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, STDERR_FILENO);
	perror(data->cmd->cmd_arg[0]);
	data->exit_status = 1;
	return (1);
}

int	ft_error_cmd(t_data *data)
{
	ft_putstr_fd(RED"minishell:", STDERR_FILENO);
	ft_putstr_fd("cannot execute\n"RESET, STDERR_FILENO);
	data->exit_status = 1;
	return (1);
}

//error during piping
int	ft_error_piping(t_data *data)
{
	ft_putstr_fd(RED"minishell: ", STDOUT_FILENO);
	ft_putstr_fd("error in pipe creation"RESET, STDOUT_FILENO);
	data->exit_status = 1;
	return (1);
}

//error during forking
int	ft_error_forking(t_data *data)
{
	ft_putstr_fd(RED"minishell: ", STDOUT_FILENO);
	ft_putstr_fd("error in fork execution\n"RESET, STDOUT_FILENO);
	data->exit_status = 1;
	return (1);
}
