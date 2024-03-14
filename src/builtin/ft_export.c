/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:51:42 by luifer            #+#    #+#             */
/*   Updated: 2024/03/14 15:49:39 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function to print the environment variables present at the moment of execution. Simple export without arguments. 
int	ft_print_export(t_cmd *cmds)
{
	while (cmds->data->env->next != NULL)
	{
		write(STDOUT_FILENO, "declare -x ", 12);
		ft_putstr_fd(cmds->data->env->env, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		cmds->data->env = cmds->data->env->next;
	}
	cmds->data->exit_status = 0;
	return (0);
}

//Function to find the node that contains the specified name of the enviroment variable
t_env	*ft_find_env_var(t_env *env, char *name)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp->next != NULL)
	{
		if (ft_strncmp(tmp->env, name, ft_strlen(name)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
//creation of new variables and assign of values
int	ft_export(t_cmd *cmds)
{
	int		i;
	char	*tmp;

	if (!(cmds->cmd_arg[1]))
		ft_print_export(cmds);
	else if (cmds->cmd_arg[1])
	{
		if (ft_find_env_var(cmds->data->env, cmds->cmd_arg[1]))//still need to divide the arg in name of the variable and content of the variable
		
	}
	while(cmds->cmd_arg[i])
	{
		
	}
	
}
*/