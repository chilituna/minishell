/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:20:19 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/20 14:30:42 by aarponen         ###   ########.fr       */
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
		return (ft_itoa(g_exit_status));
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

//Function to find the node that contains the specified name
// of the enviroment variable
t_env	*ft_find_env_var(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, name, ft_strlen(name)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

//function to sort the environment variables alphabetically
void	ft_sort_env_list(t_env *env)
{
	t_env	*tmp;
	char	*var;
	char	*value;

	tmp = env;
	while (tmp)
	{
		while (tmp->next)
		{
			if (ft_strncmp(tmp->var, tmp->next->var,
					ft_strlen(tmp->var)) > 0)
			{
				var = tmp->var;
				value = tmp->value;
				tmp->var = tmp->next->var;
				tmp->value = tmp->next->value;
				tmp->next->var = var;
				tmp->next->value = value;
				tmp = env;
			}
			else
				tmp = tmp->next;
		}
	}
}
