/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 14:10:25 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/17 14:49:02 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free all the data in the end	of the loop
void	ft_free_data(t_data *data)
{
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->pipe_fd != NULL)
	{
		ft_free_pipes(data->pipe_fd, data->cmd);
		data->pipe_fd = NULL;
	}
	if (data->lexer)
	{
		ft_free_lexer(data->lexer);
		data->lexer = NULL;
	}
	if (data->cmd)
	{
		ft_free_parser(data->cmd);
		data->cmd = NULL;
	}
	if (data->envp)
	{
		ft_free_array(data->envp);
		data->envp = NULL;
	}
}

// free the array of strings
void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// freeing the 3 strings from heredoc function
void	ft_freeall_here(char *line, char *end_line, char *env_var)
{
	free(line);
	free(end_line);
	free(env_var);
}

//should only be used in case of exit or error
void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->var);
		free(env->value);
		free(env);
		env = tmp;
	}
}
