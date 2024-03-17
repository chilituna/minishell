/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:16:58 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/17 15:18:22 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int	ft_atoi(char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			sign = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		res = ((res * 10) + (*str - 48));
		str++;
	}
	return (res * sign);
}

//function to search a variable by its name and
//update their value with a new value providen
void	ft_update_env_var(char *var, char *new_value, t_data *data)
{
	int		j;
	t_env	*tmp;

	tmp = data->env;
	while (tmp->next != NULL)
	{
		j = ft_strlen(tmp->var);
		if (ft_strncmp(tmp->var, var, j) == 0 && (var[j] == '\0'))//if found var name
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_value, data);
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
