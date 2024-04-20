/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:16:10 by luifer            #+#    #+#             */
/*   Updated: 2024/04/20 14:35:20 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function for error in duplicating file descriptor
int	ft_error_dup(void)
{
	ft_putstr_fd("minishell: "RESET, STDERR_FILENO);
	ft_putstr_fd("error duplicating file desciptor\n", STDERR_FILENO);
	g_exit_status = 1;
	return (1);
}

int	ft_error_executing(t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(data->cmd->cmd_arg[0]);
	g_exit_status = 1;
	return (1);
}

int	ft_error_cmd(void)
{
	ft_putstr_fd(RED"minishell:"RESET, STDERR_FILENO);
	ft_putstr_fd(RED"cannot execute\n"RESET, STDERR_FILENO);
	g_exit_status = 1;
	return (1);
}

//error during piping
int	ft_error_piping(void)
{
	ft_putstr_fd(RED"minishell: "RESET, STDOUT_FILENO);
	ft_putstr_fd(RED"error in pipe creation"RESET, STDOUT_FILENO);
	g_exit_status = 1;
	return (1);
}

//error during forking
int	ft_error_forking(void)
{
	ft_putstr_fd(RED"minishell: ", STDOUT_FILENO);
	ft_putstr_fd(RED"error in fork execution\n"RESET, STDOUT_FILENO);
	g_exit_status = 1;
	return (1);
}
