/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:42:06 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/21 14:38:41 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->tokens)
			ft_free_array(cmd->tokens);
		if (cmd->cmd_arg)
			ft_free_array(cmd->cmd_arg);
		if (cmd->redir)
			ft_free_redir(cmd->redir);
		free(cmd);
		cmd = tmp;
	}
}

void	ft_free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->in)
			free(redir->in);
		if (redir->out)
			free(redir->out);
		if (redir->delim)
			free(redir->delim);
		free(redir);
		redir = tmp;
	}
}

void	ft_free_pipes(int **pipe_fd, t_cmd *cmds)
{
	int	i;
	int	size;

	size = ft_list_size(cmds);
	i = 0;
	while (i < size - 1)
	{
		free(pipe_fd[i]);
		i++;
	}
	free(pipe_fd);
}

void	ft_free_and_null(char *line, t_data *data)
{
	if (!line)
		ft_heredoc_error(data);
	if (line && g_signal_nr == -1)
		free(line);
	line = NULL;
}
