/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:44:57 by luifer            #+#    #+#             */
/*   Updated: 2024/04/24 10:51:32 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to check if all characters in string are digits
int	ft_is_num(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit_code(char *str)
{
	long	code;

	if (!str)
		code = 0;
	else
		code = ft_atoi(str);
	if (code > LLONG_MAX || code < LLONG_MIN)
		code = 256;
	return (code);
}

//check for more than 1 argument
//check for only numeric values in the arguments
//check if exit value is greater than 255
//a value greater than 255 should be truncated by the
//shell and unavailable even for parent process
int	ft_exit(t_cmd *cmds)
{
	long	nbr;

	nbr = 0;
	if (cmds->cmd_arg[1] && cmds->cmd_arg[2])
	{
		ft_putstr_fd(RED"minishell: exit: too many args\n"RESET, STDERR_FILENO);
		nbr = 1;
		cmds->data->exit_status = nbr;
	}
	else if (ft_is_num(cmds->cmd_arg[1]) == 0)
		ft_error_exit(cmds);
	else
	{
		nbr = ft_exit_code(cmds->cmd_arg[1]);
		if (nbr > 255)
			nbr = nbr % 256;
		cmds->data->exit_status = nbr;
		ft_exit_minishell(cmds->data);
	}
	cmds->data->exit_status = nbr;
	return (0);
}

void	ft_error_exit(t_cmd *cmds)
{
	int	n;

	ft_putstr_fd(RED"minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmds->cmd_arg[1], STDERR_FILENO);
	ft_putstr_fd(" : numeric argument required\n"RESET, STDERR_FILENO);
	n = 2;
	cmds->data->exit_status = n;
	ft_exit_minishell(cmds->data);
}
