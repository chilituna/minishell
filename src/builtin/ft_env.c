/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:06:01 by luifer            #+#    #+#             */
/*   Updated: 2024/03/16 22:27:23 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmd *cmds)
{
	t_env	*tmp;

	tmp = cmds->data->env;
	while (tmp->next != NULL)
	{
		ft_putstr_fd(tmp->var, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(tmp->value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		tmp = tmp->next;
	}
	cmds->data->exit_status = 0;
	return (0);
}
