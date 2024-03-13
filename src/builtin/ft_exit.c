/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarpo e  <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:44:57 by luifer            #+#    #+#             */
/*   Updated: 2024/03/13 12:19:35 by aarpo e          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to check if all characters in string are digits
int	ft_is_num(const char *str)
{
	int	i;

	i = 0;
	if(!str)
		return (0);
	if(str[i] == '-' || str[i] == '+')
		i++;
	while(str[i])
	{
		if(str[i] >= '0' && str[i] <= '9')
			return (0);
		i++;
	}
	return(1);
}

int	ft_exit_code(char *str)
{
	int	code;

	if(!str[0])
		code = 0;
	else if(ft_is_num(str))
		code = ft_atoi(str);
	else
		code = -1;
	return(code);
}

int	ft_exit(t_cmd *cmds)
{
	int	nbr;

	nbr = 0;
	if (cmds->cmd_arg[1])
		nbr = ft_exit_code(cmds->cmd_arg[1]);
	if(nbr >= 256)//check if exit value is greater than 255
		cmds->data->exit_status = 2;// a value greater than 255 should be truncated by the shell and unavailable even for parent process
	else if(cmds->cmd_arg[1] && cmds->cmd_arg[2])//check for more than 1 argument
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		cmds->data->exit_status = 1;
	}
	else if(ft_is_num(cmds->cmd_arg[1]) == 1)//check for only numeric values in the arguments
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd("please provide numeric argument", STDERR_FILENO);
	}
	cmds->data->exit_status = nbr;
	ft_exit_minishell(cmds->data);
	exit(nbr);
}
