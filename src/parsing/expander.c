/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:54:16 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/20 14:57:49 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// expand environment variables and exit status
// iterate through each string in cmd_arg
// anyhing in single quotes is not expanded
// / unless single quotes are inside double quotes
// if $ is found, check if the next character is ?:
// - if it is, replace with exit status
// else if the next character is a letter or _,
// - iterate through the string until a non-alphanumeric or
//		non underscore character is found
// - save the word in a temporary variable
// - compare the word with the environment variables
// - if the environment variable is found, replace the word with the env var
// - if the environment variable is not found, replace the word with empty str
// - replace the original string with the new string
void	ft_expand_env(t_cmd *cmd, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd->cmd_arg[i])
	{
		j = 0;
		while (cmd->cmd_arg[i][j])
		{
			if (cmd->cmd_arg[i][j] == '\'')
				j = ft_skip_quotes(cmd, i, j);
			if (cmd->cmd_arg[i][j] == '\"')
				j = ft_expand_double(cmd, i, j, data);
			if (cmd->cmd_arg[i][j] == '$' && cmd->cmd_arg[i][j + 1] == '?')
				j = ft_expand_exit(cmd, i, j, data);
			else if (cmd->cmd_arg[i][j] == '$' && cmd->cmd_arg[i][j + 1]
				&& (ft_isalpha(cmd->cmd_arg[i][j + 1])
				|| cmd->cmd_arg[i][j + 1] == '_'))
				j = ft_expand_env_var(cmd, i, j, data);
			if (cmd->cmd_arg[i][j])
				j++;
		}
		i++;
	}
}

int	ft_expand_double(t_cmd *cmd, int i, int j, t_data *data)
{
	j++;
	while (cmd->cmd_arg[i][j] && cmd->cmd_arg[i][j] != '\"')
	{
		if (cmd->cmd_arg[i][j] == '$' && cmd->cmd_arg[i][j + 1] == '?')
			j = ft_expand_exit(cmd, i, j, data);
		else if (cmd->cmd_arg[i][j] == '$' && cmd->cmd_arg[i][j + 1]
			&& (ft_isalpha(cmd->cmd_arg[i][j + 1])
			|| cmd->cmd_arg[i][j + 1] == '_'))
			j = ft_expand_env_var(cmd, i, j, data);
		if (cmd->cmd_arg[i][j])
			j++;
	}
	return (j);
}

int	ft_skip_quotes(t_cmd *cmd, int i, int j)
{
	j++;
	while (cmd->cmd_arg[i][j] && cmd->cmd_arg[i][j] != '\'')
		j++;
	return (j);
}

int	ft_expand_exit(t_cmd *cmd, int i, int j, t_data *data)
{
	char	*beginnig_tmp;
	char	*exit_status;
	char	*end_tmp;
	int		new_index;

	beginnig_tmp = ft_substr(cmd->cmd_arg[i], 0, j, data);
	exit_status = ft_itoa(data->exit_status);
	new_index = j + ft_strlen(exit_status);
	end_tmp = ft_substr(cmd->cmd_arg[i], j + 2,
			ft_strlen(cmd->cmd_arg[i]) - j - 2, data);
	free(cmd->cmd_arg[i]);
	cmd->cmd_arg[i] = ft_strjoin(beginnig_tmp, exit_status, data);
	free(beginnig_tmp);
	free(exit_status);
	beginnig_tmp = cmd->cmd_arg[i];
	cmd->cmd_arg[i] = ft_strjoin(beginnig_tmp, end_tmp, data);
	free(beginnig_tmp);
	free(end_tmp);
	return (new_index);
}

int	ft_expand_env_var(t_cmd *cmd, int i, int j, t_data *data)
{
	char	*beginnig_tmp;
	char	*env_str;
	char	*env;
	char	*end;
	int		k;

	beginnig_tmp = ft_substr(cmd->cmd_arg[i], 0, j, data);
	k = j + 1;
	while (ft_isalnum(cmd->cmd_arg[i][k]) || cmd->cmd_arg[i][k] == '_')
		k++;
	env_str = ft_substr(cmd->cmd_arg[i], j + 1, k - j - 1, data);
	env = ft_getenv(env_str, data);
	free(env_str);
	end = ft_substr(cmd->cmd_arg[i], k, ft_strlen(cmd->cmd_arg[i]) - k, data);
	free(cmd->cmd_arg[i]);
	cmd->cmd_arg[i] = ft_strjoin(beginnig_tmp, env, data);
	k = j + ft_strlen(env);
	free(beginnig_tmp);
	free(env);
	beginnig_tmp = ft_strdup(cmd->cmd_arg[i], data);
	free(cmd->cmd_arg[i]);
	cmd->cmd_arg[i] = ft_strjoin(beginnig_tmp, end, data);
	free(beginnig_tmp);
	free(end);
	return (k);
}
