/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:51:42 by luifer            #+#    #+#             */
/*   Updated: 2024/03/13 21:25:12 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_export(t_cmd *cmds)
{
	extern char	**environ;//special variable with all the variable enviroment 
	int			i;

	while(environ[i] != NULL)//iterate throug the array and print the variables and their content 
	{
		write(STDOUT_FILENO, "declare -x ", 12);
		ft_putstr_fd(environ[i], STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	cmds->data->exit_status = 0;
	return(0);
}

/*
creation of new variables and assign of values
void	ft_export(t_cmd *cmds)
{
	int	i;

	if(!(cmds->cmd_arg[1]))//if export is passed without arguments
		ft_print_export(cmds);
	i = 1;
	while(cmds->cmd_arg[i])
	{
		
	}
	
}
*/