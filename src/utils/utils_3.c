/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:16:58 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/10 12:18:05 by luifer           ###   ########.fr       */
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
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while(data->env[i])
	{
		j = 0;
		while (data->env[i][j] && data->env[i][j] != '=')//search the name of variable until = sign
			j++;
		if(ft_strncmp(data->env[i], var, j) == 0 && (var[j] == '\0'))//if found var name
		{
			j++;//skip the = sign
			while(data->env[i][j] && new_value[k])//copy the new content into the variable, updating it
			{
				data->env[i][j] = new_value[k];
				j++;
				k++;
			}
		}
		i++;
	}
}
