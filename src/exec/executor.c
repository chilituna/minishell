/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:36:49 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/28 16:19:04 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//store environment variables in data
//execute the command
//if it is a builtin, execute the builtin
//if it is not a builtin, execute the command
void	ft_execute_cmds(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->builtin)
			cmd->builtin(cmd);
		else
		{
			printf("execve will be called\n");
			// TO DO: ft_execve(cmd);
		}
		cmd = cmd->next;
	}
}
