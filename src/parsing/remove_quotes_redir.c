/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:48:46 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/17 17:50:40 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove_redir_quote(char **str, int *j, t_cmd *cmd)
{
	char	*beginning;
	char	*end;

	beginning = ft_substr((*str), 0, *j, cmd->data);
	end = ft_substr((*str), *j + 1, ft_strlen(*str) - *j - 1, cmd->data);
	free(*str);
	*str = ft_strjoin(beginning, end, cmd->data);
	free(beginning);
	free(end);
	*j = 0;
}

//remove quotes in case the file name has quotes:
//iterate through the string until a quote is found
//remove all the quotes of the same type
void	ft_process_redir_quotes(char **str, t_cmd *cmd)
{
	int		j;
	char	quote;

	j = 0;
	quote = '\0';
	while ((*str)[j])
	{
		if ((*str)[j] == '\'' || (*str)[j] == '\"')
		{
			quote = (*str)[j];
			while ((*str)[j])
			{
				if ((*str)[j] == quote)
					ft_remove_redir_quote(str, &j, cmd);
				j++;
			}
		}
		j++;
	}
}
