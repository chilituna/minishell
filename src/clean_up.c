/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarpo e  <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 14:10:25 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/13 13:10:26 by aarpo e          ###   ########.fr       */
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

	// printf("lexer freed\n");
}

void	ft_free_parser(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
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
		if (cmd->cmd_arg)
			free(cmd->cmd_arg);
		if (cmd->in)
			free(cmd->in);
		if (cmd->out)
			free(cmd->out);
		if (cmd->heredoc_delim)
			free(cmd->heredoc_delim);
		if (cmd->tokens)
			free(cmd->tokens);
		free(cmd);
		cmd = tmp;
	}
	// printf("parser freed\n");
}

//should only be used in case of exit or error
void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->env);
		free(env);
		env = tmp;
	}
}
