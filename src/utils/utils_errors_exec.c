/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:16:10 by luifer            #+#    #+#             */
/*   Updated: 2024/04/10 15:54:16 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

//function for error in duplicating file descriptor
int	ft_error_dup(t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, STDOUT_FILENO);
	ft_putstr_fd(RED"error duplicating file desciptor\n"RESET, STDOUT_FILENO);
	data->exit_status = 1;
	return (1);
}

int	ft_error_closing(t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, STDOUT_FILENO);
	ft_putstr_fd(RED"error closing fd:"RESET, STDOUT_FILENO);
	data->exit_status = 1;
	return (1);
}

int	ft_error_executing(t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, STDOUT_FILENO);
	ft_putstr_fd(RED"error: cannot execute\n"RESET, STDOUT_FILENO);
	data->exit_status = 1;
	return (1);
}

int	ft_error_cmd(t_data *data)
{
	ft_putstr_fd(RED"minishell:"RESET, STDERR_FILENO);
	ft_putstr_fd(RED"cannot execute\n"RESET, STDERR_FILENO);
	data->exit_status = 1;
	return (1);
}

//error during piping
int	ft_error_piping(t_data *data)
{
	ft_putstr_fd(RED"minishell: "RESET, STDOUT_FILENO);
	ft_putstr_fd(RED"error in pipe creation"RESET, STDOUT_FILENO);
	data->exit_status = 1;
	return (1);
}

//error during forking
int	ft_error_forking(t_data *data)
{
	ft_putstr_fd(RED"minishell: ", STDOUT_FILENO);
	ft_putstr_fd(RED"error in fork execution\n"RESET, STDOUT_FILENO);
	data->exit_status = 1;
	return (1);
}

int	ft_error_opening(t_data *data, char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(file);
	data->exit_status = 1;
	return (1);
}

int	ft_error_writing(t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(data->cmd->redir->out);
	data->exit_status = 1;
	return (1);
}