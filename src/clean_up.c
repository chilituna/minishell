/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 14:10:25 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/28 16:50:11 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_data(t_data *data)
{
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->lexer)
	{
		ft_free_lexer(data->lexer);
		data->lexer = NULL;
	}
	if (data->cmd)
	{
		ft_free_parser(data->cmd);
		data->cmd = NULL;
	}

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

	printf("lexer freed\n");
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
		i = 0;
		while (cmd->cmd_arg[i])
		{
			free(cmd->cmd_arg[i]);
			i++;
		}
		free(cmd->tokens);
		free(cmd);
		cmd = cmd->next;
	}
	printf("parser freed\n");
}

//should only be used in case of exit or error
void	ft_free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
