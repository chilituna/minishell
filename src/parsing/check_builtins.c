/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:04:15 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/12 15:47:22 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if the command is a builtin
// return 1 if it is, 0 if not
int	ft_is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0 && cmd[4] == '\0')
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0 && cmd[2] == '\0')
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0 && cmd[3] == '\0')
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0 && cmd[6] == '\0')
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0 && cmd[5] == '\0')
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0 && cmd[3] == '\0')
		return (1);
	else if (ft_strncmp(cmd, "exit", 4) == 0 && cmd[4] == '\0')
		return (1);
	else
		return (0);
}

// return a function pointer to the corresponding builtin
int	(*ft_get_builtin(char *cmd))(t_cmd *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (ft_echo);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (ft_cd);
	 else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (ft_pwd);
	// else if (ft_strncmp(cmd, "export", 6) == 0)
	// 	return (ft_export);
	// else if (ft_strncmp(cmd, "unset", 5) == 0)
	// 	return (ft_unset);
	// else if (ft_strncmp(cmd, "env", 3) == 0)
	// 	return (ft_env);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return (ft_exit);
	else
		return (NULL);
}
