/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:53:45 by lperez-h          #+#    #+#             */
/*   Updated: 2024/04/14 16:46:51 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Function to generate an array with the
//environment variables inside of it
//it considers the case where there is no path
//in the case of unset of the path
static char	**ft_extract_path(t_cmd *cmds)
{
	char	**path;
	t_env	*tmp;

	tmp = ft_search_env_var(cmds->data->env, "PATH");
	if (tmp == NULL)
	{
		cmds->data->exit_status = 1;
		return (NULL);
	}
	path = ft_split(tmp->value, ':');
	return (path);
}

//This function find a valid cmd_path
//for the command received as argument
//it returns a string with the right path when is found
//null when is not found
char	*ft_find_valid_path(char *cmd, char **path, t_data *data)
{
	int		i;
	char	*cmd_path;
	char	*result;

	i = 0;
	cmd_path = ft_strjoin("/", cmd, data);
	while (path[i])
	{
		result = ft_strjoin(path[i], cmd_path, data);
		if (access(result, F_OK | X_OK) == 0)
			return (result);
		free(result);
		i++;
	}
	return (NULL);
}

//This function find the valid PATH for the specified command
//it will extract the path from env variables and find a valid
//path for the command. When a valid path is found, it is stored
//in the cmds->path field
int	ft_find_cmd_path(t_cmd *cmds, t_data *data)
{
	char		**env;
	char		*cmd_path;
	struct stat	path_stat;

	env = ft_extract_path(cmds);
	if (!env)
	{
		data->exit_status = 1;
		ft_putstr_fd(RED"minishell: could not get env\n"RESET, STDERR_FILENO);
	}
	if (cmds->cmd_arg[0][0] == '/' || cmds->cmd_arg[0][0] == '.')
	{
		if (stat(cmds->cmd_arg[0], &path_stat) == -1)
		{
			if (errno == ENOENT)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(cmds->cmd_arg[0], STDERR_FILENO);
				perror(": ");
				data->exit_status = 127;
				return (1);
			}
			else if (errno == EACCES)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(cmds->cmd_arg[0], STDERR_FILENO);
				ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
				data->exit_status = 126;
				return (1);
			}
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(cmds->cmd_arg[0], STDERR_FILENO);
				ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
				data->exit_status = 126;
				return (1);
			}
		}
		else if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmds->cmd_arg[0], STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			data->exit_status = 126;
			return (1);
		}
		else if (access(cmds->cmd_arg[0], X_OK) == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmds->cmd_arg[0], STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			data->exit_status = 126;
			return (1);
		}
		cmds->path = ft_strdup(cmds->cmd_arg[0], data);
		return (0);
	}
	cmd_path = ft_find_valid_path(cmds->cmd_arg[0], env, data);
	if (!cmd_path)
	{
		ft_putstr_fd(cmds->cmd_arg[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		data->exit_status = 127;
		return (1);
	}
	else
		cmds->path = cmd_path;
	return (0);
}
