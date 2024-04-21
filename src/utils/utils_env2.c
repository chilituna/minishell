/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:20:19 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/21 16:20:38 by aarponen         ###   ########.fr       */
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

void	ft_swap_env(t_env *env1, t_env *env2)
{
	char	*var;
	char	*value;

	var = env1->var;
	value = env1->value;
	env1->var = env2->var;
	env1->value = env2->value;
	env2->var = var;
	env2->value = value;
}

//function to sort the environment variables alphabetically
void	ft_sort_env_list(t_env *env)
{
	t_env	*tmp;
	size_t	len;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		tmp = env;
		while (tmp && tmp->next)
		{
			len = ft_strlen(tmp->var);
			if (ft_strlen (tmp->next->var) < len)
				len = ft_strlen(tmp->next->var);
			if (ft_strncmp(tmp->var, tmp->next->var, len) > 0)
			{
				ft_swap_env(tmp, tmp->next);
				swapped = 1;
			}
			tmp = tmp->next;
		}
	}
}

//create a linked list to store env variables
void	ft_copy_env(char **envp, t_data *data)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (envp[i])
	{
		name = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i], data);
		value = ft_strdup(ft_strchr(envp[i], '=') + 1, data);
		if (i == 0)
			data->env = ft_create_env(name, value);
		else
			ft_add_var_back(data->env, ft_create_env(name, value));
		i++;
	}
}
