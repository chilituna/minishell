/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 21:38:59 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/21 22:26:38 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_expand_exit_here(char **line, int i, t_data *data)
{
	char	*beginnig_tmp;
	char	*exit_status;
	char	*end_tmp;
	int		new_index;

	beginnig_tmp = ft_substr((*line), 0, i, data);
	if (g_signal_nr != -1)
	{
		exit_status = ft_itoa(g_signal_nr + 128);
		g_signal_nr = -1;
	}
	else
		exit_status = ft_itoa(data->exit_status);
	new_index = i + ft_strlen(exit_status);
	end_tmp = ft_substr((*line), i + 2,
			ft_strlen((*line)) - i - 2, data);
	free(*line);
	(*line) = ft_strjoin(beginnig_tmp, exit_status, data);
	free(beginnig_tmp);
	free(exit_status);
	beginnig_tmp = (*line);
	(*line) = ft_strjoin(beginnig_tmp, end_tmp, data);
	free(beginnig_tmp);
	free(end_tmp);
	return (new_index);
}

int	ft_expand_env_var_here(char **line, int i, t_data *data)
{
	char	*beginnig_tmp;
	char	*env_str;
	char	*env;
	char	*end;
	int		k;

	beginnig_tmp = ft_substr((*line), 0, i, data);
	k = i + 1;
	while (ft_isalnum((*line)[k]) || (*line)[k] == '_')
		k++;
	env_str = ft_substr((*line), i + 1, k - i - 1, data);
	env = ft_getenv(env_str, data);
	free(env_str);
	end = ft_substr((*line), k, ft_strlen(*line) - k, data);
	free(*line);
	(*line) = ft_strjoin(beginnig_tmp, env, data);
	k = i + ft_strlen(env);
	free(beginnig_tmp);
	free(env);
	beginnig_tmp = (*line);
	(*line) = ft_strjoin(beginnig_tmp, end, data);
	free(beginnig_tmp);
	free(end);
	return (k - 1);
}

int	ft_endofvar(char *line, int i)
{
	while (ft_isalnum(line[i]) || line[i] == '_' || line[i] == '?')
		i++;
	return (i);
}
