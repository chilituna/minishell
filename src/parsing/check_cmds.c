/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:51:53 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/17 21:03:04 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// for each command, check for redirections
// create a redirection node for each:
// (token and filename or delimeter if heredoc)
// remove directions from token array
// combine remaining words into **cmd_arg for execve
// check if command is a builtin and store a function pointer
// to the corresponding function
// if there are no commands, return 0
// expand environment variables in cmd_arg
// remove empty strings from cmd_arg
// remove quotes from cmd_arg
// check for heredoc and store into temp file

int	ft_check_cmds(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->cmd_arg = ft_check_redirections(cmd);
		if (!cmd->cmd_arg)
			return (ft_print_error("Syntax error: incorrect redirections"));
		if (cmd->cmd_arg[0] && ft_is_builtin(cmd->cmd_arg[0]))
			cmd->builtin = ft_get_builtin(cmd->cmd_arg[0]);
		if (cmd->cmd_arg[0])
			ft_expand_env(cmd, cmd->data);
		if (cmd->cmd_arg[0])
			ft_remove_empty(cmd);
		if (cmd->cmd_arg[0])
			ft_remove_quotes(cmd);
		ft_check_here_doc(cmd);
		cmd = cmd->next;
	}
	return (1);
}

char	**ft_create_new_array(t_cmd *cmd)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd->cmd_arg[i])
	{
		if (cmd->cmd_arg[i][0] != '\0')
			j++;
		i++;
	}
	new = ft_malloc(sizeof(char *) * (j + 1), cmd->data);
	return (new);
}

// remove any empty strings from cmd_arg
void	ft_remove_empty(t_cmd *cmd)
{
	int		i;
	int		j;
	char	**new;

	new = ft_create_new_array(cmd);
	i = 0;
	j = 0;
	while (cmd->cmd_arg[i])
	{
		if (cmd->cmd_arg[i][0] != '\0')
		{
			new[j] = ft_strdup(cmd->cmd_arg[i], cmd->data);
			j++;
		}
		i++;
	}
	new[j] = NULL;
	ft_free_array(cmd->cmd_arg);
	cmd->cmd_arg = new;
}
