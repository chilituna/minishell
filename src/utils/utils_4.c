/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:42:52 by lperez-h          #+#    #+#             */
/*   Updated: 2024/03/17 13:07:24 by lperez-h         ###   ########.fr       */
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
