/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 14:10:25 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/25 23:42:15 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_data(t_data *data)
{
	if (data->prompt)
		free(data->prompt);
	if (data->lexer)
		ft_free_lexer(data->lexer);
	if (data->cmd)
		ft_free_parser(data->cmd);
}

void	ft_free_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;

	while (lexer)
	{
		tmp = lexer;
		lexer = lexer->next;
		if (tmp->str)
			free(tmp->str);
		if (tmp->token)
			free(tmp->token);
		free(tmp);
	}
}

void	ft_free_parser(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		i = 0;
		while (cmd->tokens[i])
		{
			free(cmd->tokens[i]);
			i++;
		}
		free(cmd->tokens);
		free(cmd);
		cmd = cmd->next;
	}
}



