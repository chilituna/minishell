/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:23:53 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/24 11:03:44 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quoted_redir(int i, char *str)
{
	if (str[i] == '>' || str[i] == '<')
	{
		ft_print_error("Syntax error: incorrect redirections");
		return (-1);
	}
	if (str[i] == '\'')
		i += ft_quoted_string(str + i);
	else if (str[i] == '\"')
		i += ft_quoted_string(str + i);
	while (str[i] != '\0' && !ft_isspace(str[i]) && str[i] != '|')
		i++;
	return (i);
}

int	ft_iterate_until_end(char *str, int i)
{
	while (str[i] != '\0' && !ft_isspace(str[i]))
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += ft_quoted_string(str + i);
		else
			i++;
	}
	return (i);
}

// break the input into strings:
// skip whitespace
// put quoted text into a single string
// split by redirections
// split by pipes
// otherwise, split by space
// create a string and store in a linked list
// return the remaining input
char	*ft_pick_string(char *str, t_lexer *lexer)
{
	int		start;
	int		i;

	i = 0;
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	start = i;
	if (lexer->prev && lexer->prev->token
		&& (!ft_strncmp(lexer->prev->token, "REDIR", 5)))
	{
		i = ft_quoted_redir(i, str);
		if (i == -1)
			return (NULL);
	}
	else if (str[i] == '|')
		i++;
	else if (str[i] == '>' || str[i] == '<')
		i = ft_pick_redir(str, i, start, lexer);
	else
		i = ft_iterate_until_end(str, i);
	lexer->str = ft_substr(str, start, i - start, lexer->data);
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	return (str + i);
}

int	ft_pick_redir(char *str, int i, int start, t_lexer *lexer)
{
	(void)start;
	(void)lexer;
	if (str[i + 1] == str[i])
		i++;
	return (i + 1);
}

int	ft_quoted_string(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i] == '\'' || str[i] == '\"')
	{
		quote = str[i];
		i++;
		while (str[i] != '\0' && str[i] != quote)
			i++;
		i++;
	}
	return (i);
}
