/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:16:05 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/20 17:24:38 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check for whitespace
int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

// check for alphanumeric characters
int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

// check for aplhabetic characters
int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
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
