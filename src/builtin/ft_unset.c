/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:47:04 by lperez-h          #+#    #+#             */
/*   Updated: 2024/04/20 14:30:31 by aarponen         ###   ########.fr       */
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
		i = 1;
		while (cmds->cmd_arg[i])
		{
			tmp = ft_search_env_var(cmds->data->env, cmds->cmd_arg[i]);
			if (tmp)
				ft_delete_env_var(&cmds->data->env, tmp->var);
			i++;
		}
	}
	g_exit_status = 0;
	return (0);
}
