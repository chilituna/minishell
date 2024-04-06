/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:20:19 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/06 17:22:24 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get environment variable from data->env
// for $?, give exit_status from data node
// if the environment variable is not found, return empty string
char	*ft_getenv(char *var, t_data *data)
{
	int		j;
	char	*env_var;
	t_env	*tmp;

	tmp = data->env;
	if (ft_strncmp(var, "?", 1) == 0)
		return (ft_itoa(data->exit_status));
	while (tmp)
	{
		j = ft_strlen(tmp->var);
		if (ft_strncmp(tmp->var, var, j) == 0 && var[j] == '\0' && tmp->value)
		{
			env_var = ft_strdup(tmp->value, data);
			return (env_var);
		}
		tmp = tmp->next;
	}
	return (ft_strdup("", data));
}
