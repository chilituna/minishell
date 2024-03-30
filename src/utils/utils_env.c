/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:21:27 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/30 17:40:29 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function to search a variable by its name and
//update their value with a new value providen
void	ft_update_env_var(char *var, char *new_value, t_data *data)
{
	int		j;
	int		k;
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		j = ft_strlen(tmp->var);
		k = ft_strlen(var);
		if (k == j && ft_strncmp(tmp->var, var, j) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_value, data);
			free(var);
			free(new_value);
			return ;
		}
		tmp = tmp->next;
	}
}

t_env	*ft_create_env(char *name, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->var = name;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	ft_add_var_back(t_env *env, t_env *new_env)
{
	t_env	*tmp;

	if (env == NULL && new_env == NULL)
		return ;
	tmp = env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_env;
}

//Function to search and environment variable by
//the name. It returns a pointer to the node containing
//the environment variable if found, else it returns Null.
t_env	*ft_search_env_var(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, name, ft_strlen(name)) == 0
			&& tmp->var[ft_strlen(name)] == '\0')
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

//Function to search a enviroment variable and unset it
//it delete in place the linked list when found
void	ft_delete_env_var(t_env *env, char *name)
{
	t_env	*tmp;
	t_env	*to_remove;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, name, ft_strlen(name)) == 0)
		{
			to_remove = tmp;
			tmp = tmp->next;
			free(to_remove);
			return ;
		}
		else if (ft_strncmp(tmp->next->var, name, ft_strlen(name)) == 0)
		{
			to_remove = tmp->next;
			tmp->next = tmp->next->next;
			free(to_remove);
			return ;
		}
		tmp = tmp->next;
	}
}
