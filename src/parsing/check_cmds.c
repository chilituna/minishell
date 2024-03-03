/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:51:53 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/03 16:56:49 by aarponen         ###   ########.fr       */
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

int	ft_check_cmds(t_cmd *cmd)
{

	while (cmd)
	{
		cmd->cmd_arg = ft_check_redirections(cmd);
		if (!cmd->cmd_arg)
		{
			printf(RED "Error: Incorrect redirections\n" RESET);
			return (0);
		}
		if (cmd->cmd_arg[0] == NULL)
		{
			printf(RED "Error: Missing commands\n" RESET);
			return (0);
		}
		if (ft_is_builtin(cmd->cmd_arg[0]))
		{
			printf("builtin found\n");
			cmd->builtin = ft_get_builtin(cmd->cmd_arg[0]);
		}
		if (cmd->cmd_arg[0])
			ft_expand_env(cmd, cmd->data);
		cmd = cmd->next;
	}
	return (1);
}




