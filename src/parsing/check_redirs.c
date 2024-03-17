/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:34:41 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/17 18:44:18 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// iterate to the last redir struct in the linked list
// check for input and output redirections and store them in redir struct
// which is part of the cmd struct
// remove redirections from the token array by replacing them with empty strings
int	ft_store_redirection(t_cmd *cmd, int i)
{
	t_redir	*tmp;

	tmp = cmd->redir;
	while (tmp->next)
		tmp = tmp->next;
	if (!cmd->tokens[i + 1])
		return (0);
	if (ft_strncmp(cmd->tokens[i], "REDIR_HEREDOC", 13) == 0)
	{
		tmp->heredoc = 1;
		tmp->delim = ft_strdup(cmd->tokens[i + 1], cmd->data);
	}
	else if (ft_strncmp(cmd->tokens[i], "REDIR_IN", 8) == 0)
		tmp->in = ft_strdup(cmd->tokens[i + 1], cmd->data);
	else
		tmp->out = ft_strdup(cmd->tokens[i + 1], cmd->data);
	if (ft_strncmp(cmd->tokens[i], "REDIR_APPEND", 12) == 0)
		tmp->append = 1;
	cmd->tokens[i + 1] = ft_strdup("", cmd->data);
	cmd->tokens[i] = ft_strdup("", cmd->data);
	return (1);
}

t_redir	*ft_init_first_redir(t_cmd *cmd)
{
	cmd->redir = ft_malloc(sizeof(t_redir), cmd->data);
	cmd->redir->in = NULL;
	cmd->redir->out = NULL;
	cmd->redir->heredoc = 0;
	cmd->redir->delim = NULL;
	cmd->redir->append = 0;
	cmd->redir->next = NULL;
	return (cmd->redir);
}

// if !cmd->redir, initialize redir struct
// else, add a new redir struct to the linked list
// return the new redir struct
t_redir	*ft_init_redir(t_cmd *cmd)
{
	t_redir	*new;
	t_redir	*tmp;

	if (!cmd->redir)
		return (ft_init_first_redir(cmd));
	else
	{
		tmp = cmd->redir;
		while (tmp->next)
			tmp = tmp->next;
		new = ft_malloc(sizeof(t_redir), cmd->data);
		new->in = NULL;
		new->out = NULL;
		new->heredoc = 0;
		new->delim = NULL;
		new->append = 0;
		new->next = NULL;
		tmp->next = new;
		return (new);
	}
}

// check for redirections and store in the redir struct
// save anything else in cmd_arg for execution
char	**ft_check_redirections(t_cmd *cmd)
{
	int		i;
	int		redir_count;
	char	**cmd_arg;

	i = 0;
	redir_count = 0;
	while (cmd->tokens[i])
	{
		if (ft_strncmp(cmd->tokens[i], "REDIR", 5) == 0)
		{
			ft_init_redir(cmd);
			if (ft_store_redirection(cmd, i) == 0)
				return (NULL);
			redir_count += 2;
		}
		i++;
	}
	cmd_arg = ft_malloc((i - redir_count + 1) * sizeof(char *), cmd->data);
	return (ft_create_cmd_arg(cmd_arg, cmd));
}

char	**ft_create_cmd_arg(char **cmd_arg, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->tokens[i])
	{
		if (cmd->tokens[i][0] != '\0')
		{
			cmd_arg[j] = ft_strdup(cmd->tokens[i], cmd->data);
			j++;
		}
		i++;
	}
	cmd_arg[j] = NULL;
	return (cmd_arg);
}
