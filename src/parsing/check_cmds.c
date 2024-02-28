/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:51:53 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/28 15:33:16 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check for redirections and store in the cmd
//save anything else in cmd_arg for execve and return it

char	**ft_check_redirections(t_cmd *cmd)
{
	int		i;
	char	*cmd_str;

	cmd_str = ft_strdup("", cmd->data);
	i = 0;
	while (cmd->tokens[i])
	{
		if (ft_strncmp(cmd->tokens[i], "REDIR", 5) == 0)
		{
			printf("Redir found and will be stored");
			// TO DO
		}
		else
		{
			cmd_str = ft_strjoin(cmd_str, cmd->tokens[i]);
			cmd_str = ft_strjoin(cmd_str, " ");
		}
		i++;
	}
	return (ft_split(cmd_str, ' '));
}


// for each command, check for redirections
// create a redirection node for each:
// (token and filename or delimeter if heredoc)
// remove directions from token array
// combine remaining words into **cmd_arg for execve
// check if command is a builtin and store a function pointer
// to the corresponding function


void	ft_check_cmds(t_cmd *cmd)
{

	while (cmd)
	{
		cmd->cmd_arg = ft_check_redirections(cmd);
		if (ft_is_builtin(cmd->cmd_arg[0]))
		{
			cmd->builtin = ft_get_builtin(cmd->cmd_arg[0]);
			printf("builtin found\n");
		}
		cmd = cmd->next;
	}
}


// check if the command is a builtin
// return 1 if it is, 0 if not
int	ft_is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	else
		return (0);
}

// return a function pointer to the corresponding builtin
int	(*ft_get_builtin(char *cmd))(t_cmd *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (ft_echo);
	// else if (ft_strncmp(cmd, "cd", 2) == 0)
	// 	return (ft_cd);
	// else if (ft_strncmp(cmd, "pwd", 3) == 0)
	// 	return (ft_pwd);
	// else if (ft_strncmp(cmd, "export", 6) == 0)
	// 	return (ft_export);
	// else if (ft_strncmp(cmd, "unset", 5) == 0)
	// 	return (ft_unset);
	// else if (ft_strncmp(cmd, "env", 3) == 0)
	// 	return (ft_env);
	// else if (ft_strncmp(cmd, "exit", 4) == 0)
	// 	return (ft_exit);
	else
		return (NULL);
}

