/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:51:04 by lperez-h          #+#    #+#             */
/*   Updated: 2024/03/16 15:57:20 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//update the variable pwd or oldpwd as required
int	ft_update_pwd(char *var, t_data *data)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)) != NULL)//check if the current working dir is copied into buffer
		ft_update_env_var(var, buffer, data);//update the content of the variable passed
	return (1);
}

//update oldpwd with the current directory before change directory
//change directory to path and update pwd env variable
//if change directory fails check error type
int	ft_change_dir(char *path, t_data *data)
{
	ft_update_pwd("OLDPWD", data);//update oldpwd before changing directory (keep track of previous working directory)
	if (!chdir(path) && ft_update_pwd("PWD", data)) //if change path and update pwd update status successfully changed directory
		data->exit_status = 0;
	else
	{
		if (access(path, F_OK) == -1)
			ft_putstr_fd(RED"minishell: cd: no such file or directory\n"RESET, STDERR_FILENO);
		else if (access(path, R_OK | W_OK | X_OK) == -1)
			ft_putstr_fd(RED"minishell: cd: permission denied\n"RESET, STDERR_FILENO);
		data->exit_status = 1;
	}
	return (1);
}

int	ft_cd(t_cmd *cmds)
{
	char	*path_home;

	if (cmds->cmd_arg[2])//if there are more than 1 argument?
	{
		ft_putstr_fd(RED"minishell: cd: too many arguments\n"RESET, STDERR_FILENO);
		cmds->data->exit_status = 1;//update status to 1 (error)
		return (1);
	}
	if (cmds->cmd_arg[1][0] == '/')
		ft_change_dir(cmds->cmd_arg[1], cmds->data);
	path_home = ft_get_env_var("HOME", cmds->data);//search for the HOME env variable
	if (!(cmds->cmd_arg[1]) && ft_change_dir(path_home, cmds->data))//if there are no arguments just cd and the change of directory is success
		cmds->data->exit_status = 0;
	else
	{
		if (!ft_strncmp(cmds->cmd_arg[1], "--", 2) && ft_change_dir(path_home, cmds->data))//check in the case that is cd -- and move to home
		{
			cmds->data->exit_status = 0;
			return (0);
		}
		ft_change_dir(cmds->cmd_arg[1], cmds->data);//change to specified path by user in arguments
	}
	return (0) ;//give prompt back to user
}
