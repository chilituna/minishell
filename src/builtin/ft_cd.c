/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:51:04 by lperez-h          #+#    #+#             */
/*   Updated: 2024/04/20 14:59:37 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//update the variable pwd or oldpwd as required
//check if the current working dir is copied into buffer
//update the content of the variable passed
int	ft_update_pwd(char *var, t_data *data)
{
	char	buffer[PATH_MAX];
	char	*new_value;

	if (getcwd(buffer, sizeof(buffer)) != NULL)
	{
		new_value = ft_strdup(buffer, data);
		ft_update_env_var(var, new_value, data);
		free(new_value);
	}
	return (1);
}

//update oldpwd with the current directory before change directory
//change directory to path and update pwd env variable
//if change directory fails check error type
//update oldpwd before changing directory
// (keep track of previous working directory)
int	ft_change_dir(char *path, t_data *data)
{
	ft_update_pwd("OLDPWD", data);
	if (!chdir(path) && ft_update_pwd("PWD", data))
		data->exit_status = 0;
	else
	{
		if (access(path, F_OK) == -1)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		}
		else if (access(path, R_OK | W_OK | X_OK) == -1)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putstr_fd("Permission denied\n", STDERR_FILENO);
		}
		data->exit_status = 1;
	}
	return (1);
}

//if there are more than 1 argument print error
//search for the HOME env variable
//if there are no arguments just cd and the change of directory is success
//check in the case that is cd -- and move to home
//change to specified path by user in arguments
//give prompt back to user
int	ft_cd(t_cmd *cmds)
{
	char	*path_home;
	t_env	*tmp;

	tmp = ft_find_env_var(cmds->data->env, "HOME");
	path_home = tmp->value;
	if (!cmds->cmd_arg[1])
	{
		ft_change_dir(path_home, cmds->data);
		return (0);
	}
	if (cmds->cmd_arg[2])
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
		cmds->data->exit_status = 1;
		return (1);
	}
	if (cmds->cmd_arg[1][0] == '/')
		ft_change_dir(cmds->cmd_arg[1], cmds->data);
	else
		ft_change_dir(cmds->cmd_arg[1], cmds->data);
	return (0);
}
