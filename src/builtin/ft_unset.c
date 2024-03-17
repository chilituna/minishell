/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:47:04 by lperez-h          #+#    #+#             */
/*   Updated: 2024/03/16 23:41:50 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function unset several variables at the time
//will check for variable name and will delete when it found it
int	ft_unset(t_cmd *cmds)
{
	t_env	*tmp;
	int		i;

	tmp = cmds->data->env;
	if (cmds->cmd_arg[1])
	{
		i = 0;
		while(cmds->cmd_arg[i])
		{
			tmp = ft_search_env_var(cmds->data->env, cmds->cmd_arg[i]);
			if(tmp == NULL)//not found the variable
				return (1);
			else//variable is found
				ft_delete_env_var(cmds->data->env, tmp->var);
			i++;
		}
	}
	cmds->data->exit_status = 0;
	return(0);
}
