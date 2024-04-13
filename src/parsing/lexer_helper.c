/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:23:53 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/13 18:42:42 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (ft_isspace(str[i]))
		i++;
	start = i;
	if (lexer->prev && lexer->prev->token && (!ft_strncmp(lexer->prev->token, "REDIR", 5)))
	{
		while (!ft_isspace(str[i]) && str[i] != '\0' && str[i] != '|')
			i++;
	}
	else if (str[i] == '|')
	{
		lexer->str = ft_substr(str, start, 1, lexer->data);
		i++;
	}
	else if (str[i] == '>' || str[i] == '<')
		i = ft_pick_redir(str, i, start, lexer);
	else if (str[i] == '\'')
		i += ft_quoted_string(str + i, '\'');
	else if (str[i] == '\"')
		i += ft_quoted_string(str + i, '\"');
	else
	{
		while (!ft_isspace(str[i]) && str[i] != '\0' && str[i] != '|' && str[i] != '<' && str[i] != '>')
			i++;
	}
	lexer->str = ft_substr(str, start, i - start, lexer->data);
	while (ft_isspace(str[i]))
		i++;
	return (str + i);
}

int	ft_pick_redir(char *str, int i, int start, t_lexer *lexer)
{
	if (str[i + 1] == str[i])
	{
		lexer->str = ft_substr(str, start, 2, lexer->data);
		i++;
	}
	else
		lexer->str = ft_substr(str, start, 1, lexer->data);
	return (i + 1);
}

int	ft_quoted_string(char *str, char c)
{
	int		i;

	i = 0;
	i++;
	while (str[i] != c && str[i] != '\0')
		i++;
	while (!ft_isspace(str[i]) && str[i] != '\0')
		i++;
	i++;
	return (i);
}
