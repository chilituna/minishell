/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:06:01 by luifer            #+#    #+#             */
/*   Updated: 2024/03/14 11:32:36 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmd *cmds)
{
	while (cmds->data->env->next != NULL)
	{
		ft_putstr_fd(cmds->data->env->env, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		cmds->data->env = cmds->data->env->next;
	}
	cmds->data->exit_status = 0;
	return (0);
}
