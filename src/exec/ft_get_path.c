/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:53:45 by lperez-h          #+#    #+#             */
/*   Updated: 2024/03/25 17:21:46 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//This function takes 2 strings and join them to form the PATH
//it takes 2 strings as parameters and concatenate them to form a
//valid PATH.
char	*ft_get_cmd_path(t_cmd *cmds, char *path, char *tmp)
{
	char	*cmd_path;
	int		len;

	(void)cmds;
	len = ft_strlen(path);
	cmd_path = (char *)malloc(sizeof(char) * (len + 1));
	if (!cmd_path)
	{
		free(path);
		free(tmp);
		return (NULL);
	}
	ft_strlcpy(cmd_path, path, len + 1);
	free(path);
	free(tmp);
	return (cmd_path);
}

//This function find the valid PATH for the specified command
//it will take the PATH and split it using the ':' as delimitator
//then it will iterate in the 2d array searching for a valid path
//for the specified command. When a valid PATH is found it will
//call the ft_get_cmd_path function, else it will return NULL
char	*ft_find_cmd_path(t_cmd *cmds, t_data *data)
{
	char	**path;
	char	*tmp_path;
	char	*result;
	int		i;

	i = 0;
	path = ft_split(cmds->path, ':');
	result = ft_strjoin("/", cmds->cmd_arg[0], data);
	while (path[i])
	{
		tmp_path = ft_strjoin(path[i], result, data);
		if (access(tmp_path, F_OK) == 0)
		{
			free(result);
			result = tmp_path;
			break ;
		}
		free(tmp_path);
		i++;
	}
	return (result);
}
