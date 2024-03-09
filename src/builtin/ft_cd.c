/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:51:04 by lperez-h          #+#    #+#             */
/*   Updated: 2024/03/09 19:47:38 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_pwd(t_cmd *cmds)
{
	char	buffer[PATH_MAX];
	char	*tmp_1;
	char	*tmp_2;
	char	*var;
	
	if(getcwd(buffer, sizeof(buffer)) != NULL)//check if the current working dir is copied into buffer
	{
		//cmds->data->env;// I still need to search for the env variable in the array to get the env variable name
		 cd ../
		var = ft_get_env_var("PWD", cmds->data);//get the env variable name
		cmds->data->env = ft_strjoin(var, cmds->cmd_arg[1]);//copy the variable name = path stored in buffer
	}
	return(1);
}

int	ft_change_dir(t_cmd *cmds)
{
	ft_update_pwd("OLDPWD");//update oldpwd before changing directory (keep track of previous working directory)
	if(!chdir(cmds->cmd_arg) && ft_update_pwd("PWD"))//succesfully changed directory
		//return(0)? ->how do I save the succesfull status of the change of directory? 
	else
	{
		if(access(cmds->cmd_arg, F_OK) == -1)
			write(2, RED"minishell: cd: no such file or directory\n"RESET, 42);
		else if(access(cmds->cmd_arg, R_OK || W_OK || X_OK) == -1)
			write(2, RED"minishell: cd: permission denied\n"RESET, 34);
		write(2, cmds->cmd_arg[1], ft_strlen(cmds->cmd_arg[1]));
		write(2, "\n", 1);
		cmds->data->exit_status = 1;
	}
}

void	execute_cd(t_cmd *cmds)
{
	char	*path_home;
	char	*abs_path;
	char	*env_var;

	if(cmds->cmd_arg[2])//how to check if there are more than 1 argument? 
	{
		write (1, "minishell: cd: too many arguments\n", 35);
		cmds->data->exit_status = 1;//update status to 1 (error)
		return(EXIT_FAILURE);
	}
	env_var = ft_get_env_var(cmds->cmd_arg, cmds->data);//save env var
	if(cmds->cmd_arg[1][0] == '/')
		abs_path = cmds->cmd_arg[1];
	path_home = ft_get_env_var("HOME", cmds->data->env);//search for the HOME env variable
	if(!(cmds->cmd_arg[1]) && ft_change_dir(path_home))//if there are no arguments just cd and the change of directory is success
		return(0);//sucess?
	else
	{
		if(!ft_strncmp(cmds->cmd_arg[1], "--", 2) && ft_change_dir(path_home))//check in the case that is cd -- and move to home
			return(0);//success?
		ft_change_dir(cmds->cmd_arg[1]);//change to specified path by user in arguments
	}
	return(EXIT_SUCCESS);//give prompt back to user
}


/*
1) update enviroment variables 

curr_directory = pwd;
t_cmd->data->env (envir)
str1 = current path
str2 = future path

search for env variables 
!!!use ft_get_env_variable in expander.c!!!!

once found -> update content of enviroment variable
			-> save the current directory (str1)
			-> concatenate (variable name = current work directory)
*/

/*
change directory 
OLDPWD 
*/