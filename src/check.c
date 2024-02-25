/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:07:49 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/25 23:20:41 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_quotes(char *input)
{
	int	single_q;
	int	double_q;

	single_q = ft_check_singlequotes(input);
	double_q = ft_check_doublequotes(input);
	if (single_q % 2 != 0 || double_q % 2 != 0)
	{
		printf(RED "ERROR: unclosed quotes\n" RESET);
		return (0);
	}
	return (1);
}

int	ft_check_doublequotes(char *input)
{
	int	double_q;

	double_q = 0;
	while (*input != '\0')
	{
		if (*input == '\'')
		{
			input = ft_strchr(input + 1, '\'');
			if (input == NULL)
				return (1);
		}
		if (*input == '\"')
		{
			double_q++;
			input = ft_strchr(input + 1, '\"');
			if (input == NULL)
				return (1);
			double_q++;
		}
		input++;
	}
	return (double_q);
}

int	ft_check_singlequotes(char *input)
{
	int	single_q;

	single_q = 0;
	while (*input != '\0')
	{
		if (*input == '\"')
		{
			input = ft_strchr(input + 1, '\"');
			if (input == NULL)
				return (1);
		}
		if (*input == '\'')
		{
			single_q++;
			input = ft_strchr(input + 1, '\'');
			if (input == NULL)
				return (1);
			single_q++;
		}
		input++;
	}
	return (single_q);
}
