/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarpo e  <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:16:58 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/13 13:20:11 by aarpo e          ###   ########.fr       */
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
	while(*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if(*str == 43 || *str == 45)
	{
		if(*str == 45)
			sign = -1;
		str++;
	}
	while(*str >= 48 && *str <= 57)
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
	int		k;
	t_env	*tmp;

	k = 0;
	tmp = data->env;
	while (tmp->env)
	{
		j = 0;
		while (tmp->env[j] && tmp->env[j] != '=')//search the name of variable until = sign
			j++;
		if(ft_strncmp(tmp->env, var, j) == 0 && (var[j] == '\0'))//if found var name
		{
			j++;//skip the = sign
			while(tmp->env[j] && new_value[k])//copy the new content into the variable, updating it
			{
				tmp->env[j] = new_value[k];
				j++;
				k++;
			}
		}
		tmp = tmp->next;
	}
}
