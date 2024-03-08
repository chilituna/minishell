/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:51:04 by lperez-h          #+#    #+#             */
/*   Updated: 2024/03/08 22:18:10 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_cmd *cmds)
{
	char	buffer[PATH_MAX];
	char	*tmp_1;
	char	*tmp_2;
	
	if(getcwd(buffer, sizeof(buffer)) != NULL)//check if the current working dir is copied into buffer
	{
		//cmds->data->env;// I still need to search for the env variable in the array to get the env variable name
		tmp_1 = ft_strdup(buffer, cmds->data);//copy the current work directory into temporary
		tmp_2 = ft_strjoin(cmds->cmd_arg, "=", cmds->data);//copy the input str (arguments received + = sign)
		cmds->data->env = ft_strjoin(tmp_1, tmp_2, cmds->data);//check how do I update the value of the env variable inside the **env array
		free(tmp_1);
		free(tmp_2);
	}

	path = cmds->cmd_arg;//Here I get the path where I want to move

	if(!path)
	{
		if(HOME)//
			chdir(HOME);
	}
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