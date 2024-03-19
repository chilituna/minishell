/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:42:52 by lperez-h          #+#    #+#             */
/*   Updated: 2024/03/19 21:25:28 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"minishell.h"

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

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while ((i < size - 1) && (src[i] != '\0'))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return(ft_strlen(src));
}
