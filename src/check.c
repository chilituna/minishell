/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarpo e  <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:07:49 by aarpo e           #+#    #+#             */
/*   Updated: 2024/02/21 17:45:01 by aarpo e          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check input for unclosed quotes
int	ft_check_quotes(char *input)
{
	int		i;
	int		single_q;
	int		double_q;

	i = 0;
	single_q = 0;
	double_q = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			single_q++;
		if (input[i] == '\"')
			double_q++;
		i++;
	}
	if (single_q % 2 != 0 || double_q % 2 != 0)
	{
		printf(RED "ERROR: unclosed quotes\n" RESET);
		return (1);
	}
	return (0);
}


