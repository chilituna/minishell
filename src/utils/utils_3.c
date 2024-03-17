/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:16:58 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/17 18:46:51 by aarponen         ###   ########.fr       */
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

//function to check that all the letters in a string are capital letters
//returns 0 if all the letters are upper case, 1 if not.
int	ft_all_capitals(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (name[i] >= 65 && name[i] <= 90)
			i++;
		else
			return (1);
	}
	return (0);
}
