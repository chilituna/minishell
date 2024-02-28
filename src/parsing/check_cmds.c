/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:51:53 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/28 21:23:25 by aarponen         ###   ########.fr       */
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



//check for input and output redirections and store them in the cmd
int	ft_store_redirection(t_cmd *cmd, int i)
{
	if (ft_strncmp(cmd->tokens[i], "REDIR_IN", 8) == 0)
	{
		if (i == 0)
			return (0);
		cmd->in = ft_strdup(cmd->tokens[i - 1], cmd->data);
		cmd->tokens[i - 1] = ft_strdup("", cmd->data);
		cmd->tokens[i] = ft_strdup("", cmd->data);
	}
	if (ft_strncmp(cmd->tokens[i], "REDIR_OUT", 9) == 0)
	{
		if (!cmd->tokens[i + 1])
			return (0);
		cmd->out = ft_strdup(cmd->tokens[i + 1], cmd->data);
		cmd->tokens[i + 1] = ft_strdup("", cmd->data);
		cmd->tokens[i] = ft_strdup("", cmd->data);
	}
	return (1);
}

//check for redirections and store in the cmd:
//save anything else in cmd_arg for execution and return it
char	**ft_check_redirections(t_cmd *cmd)
{
	int		i;
	int		j;
	int		cmd_count;
	char	**cmd_arg;

	i = 0;
	cmd_count = 0;
	while (cmd->tokens[i])
	{
		if (ft_strncmp(cmd->tokens[i], "REDIR", 5) == 0)
		{
			printf("Redir found and will be stored\n");
			if (!ft_store_redirection(cmd, i))
				return (NULL);
			cmd_count -= 2;
		}
		i++;
	}
	cmd_arg = ft_malloc((i - cmd_count) * sizeof(char *), cmd->data);
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
		if (ft_is_builtin(cmd->cmd_arg[0]))
		{
			cmd->builtin = ft_get_builtin(cmd->cmd_arg[0]);
			printf("builtin found\n");
		}
		cmd = cmd->next;
	}
	return (1);
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

