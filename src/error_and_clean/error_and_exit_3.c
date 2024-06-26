/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:59:10 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/20 18:38:52 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_file(t_data *data, char *file)
{
	ft_putstr_fd(RED"minishell: "RESET, STDERR_FILENO);
	perror(file);
	data->exit_status = 1;
	return (1);
}

int	ft_error_closing(t_data *data)
{
	ft_putstr_fd(RED"minishell: ", STDERR_FILENO);
	ft_putstr_fd("error closing fd:"RESET, STDERR_FILENO);
	data->exit_status = 1;
	return (1);
}

int	ft_path_error_1(t_data *data, char *file)
{
	ft_putstr_fd(RED"minishell: "RESET, STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	perror(": ");
	data->exit_status = 127;
	return (1);
}

int	ft_path_error_2(t_data *data, char *file)
{
	ft_putstr_fd(RED"minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n"RESET, STDERR_FILENO);
	data->exit_status = 126;
	return (1);
}

int	ft_path_error_3(t_data *data, char *file)
{
	ft_putstr_fd(RED"minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n"RESET, STDERR_FILENO);
	data->exit_status = 126;
	return (1);
}
