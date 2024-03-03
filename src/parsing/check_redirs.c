/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:34:41 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/03 18:04:39 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check for input and output redirections and store them in the cmd
// remove redirections from the token array by replacing them with empty strings
int	ft_store_redirection(t_cmd *cmd, int i)
{
	if (!cmd->tokens[i + 1])
		return (0);
	if (ft_strncmp(cmd->tokens[i], "REDIR_HEREDOC", 13) == 0)
	{
		cmd->heredoc = 1;
		cmd->heredoc_delim = ft_strdup(cmd->tokens[i + 1], cmd->data);
	}
	else if (ft_strncmp(cmd->tokens[i], "REDIR_IN", 8) == 0)
		cmd->in = ft_strdup(cmd->tokens[i + 1], cmd->data);
	else
		cmd->out = ft_strdup(cmd->tokens[i + 1], cmd->data);
	if (ft_strncmp(cmd->tokens[i], "REDIR_APPEND", 12) == 0)
		cmd->append = 1;
	cmd->tokens[i + 1] = ft_strdup("", cmd->data);
	cmd->tokens[i] = ft_strdup("", cmd->data);
	return (1);
}

// check for redirections and store in the cmd:
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
