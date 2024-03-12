/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:54:16 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/12 17:32:36 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// expand environment variables in cmd_arg:
// iterate through each word in cmd_arg:
// if $ is found, save the word in a temporary variable
// iterate through each environment variable:
// if the environment variable is found, replace the word with the env var:
// save the beginning of the string, remove the $word,
// join with the env var, join with the rest of the string
// if the environment variable is not found, replace the word with empty str
void	ft_expand_env(t_cmd *cmd, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (cmd->cmd_arg[i])
	{
		j = 0;
		if (cmd->cmd_arg[i][j] != '\'')
			ft_check_for_env(cmd, i, j, data);
		i++;
	}
}

void	ft_check_for_env(t_cmd *cmd, int i, int j, t_data *data)
{
	char	*beginnig_tmp;
	char	*env_var;
	char	*end_tmp;
	int		k;

	while (cmd->cmd_arg[i][j])
	{
		if (cmd->cmd_arg[i][j] == '\'')
		{
			j++;
			while (cmd->cmd_arg[i][j] && j + 1 < (int)ft_strlen(cmd->cmd_arg[i]) && cmd->cmd_arg[i][j] != '\'')
				j++;
		}
		if (cmd->cmd_arg[i][j] == '$' && cmd->cmd_arg[i][j + 1])
		{
			beginnig_tmp = ft_substr(cmd->cmd_arg[i], 0, j, data);
			k = j + 1;
			while (isalnum(cmd->cmd_arg[i][k]) || cmd->cmd_arg[i][k] == '_' || cmd->cmd_arg[i][k] == '?')
				k++;
			env_var = ft_get_env_var(ft_substr(cmd->cmd_arg[i], j + 1, k - j - 1, data), data);
			end_tmp = ft_substr(cmd->cmd_arg[i], k, ft_strlen(cmd->cmd_arg[i]) - k, data);
			free(cmd->cmd_arg[i]);
			cmd->cmd_arg[i] = ft_strjoin(beginnig_tmp, env_var, data);
			free(beginnig_tmp);
			free(env_var);
			beginnig_tmp = cmd->cmd_arg[i];
			cmd->cmd_arg[i] = ft_strjoin(beginnig_tmp, end_tmp, data);
			free(beginnig_tmp);
			free(end_tmp);
			j = k - 1;
			if (j >= (int)ft_strlen(cmd->cmd_arg[i]))
				break ;
		}
		j++;
	}
}

// get environment variable from data->env
// for $?, give exit_status from data node
// if the environment variable is not found, return empty string
char	*ft_get_env_var(char *var, t_data *data)
{
	int		i;
	int		j;
	char	*env_var;

	i = 0;

	if (var[0] == '?')
	{
		free(var);
		return (ft_itoa(data->exit_status));
	}
	while (data->env[i])
	{
		j = 0;
		while (data->env[i][j] && data->env[i][j] != '=')
			j++;
		if (ft_strncmp(data->env[i], var, j) == 0 && var[j] == '\0')
		{
			env_var = ft_strdup(data->env[i] + j + 1, data);
			free(var);
			return (env_var);
		}
		i++;
	}
	free(var);
	return (ft_strdup("", data));
}
