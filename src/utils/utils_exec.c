/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 03:49:10 by luifer            #+#    #+#             */
/*   Updated: 2024/04/20 14:30:31 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Convert the environment list into an array
//it iterates through the list joining the variable name
//with their respective value and save each one into the array
//it returns the array once it traverse the whole list.
char	**ft_convert_env_list_to_array(t_env *env, t_cmd *cmds)
{
	int		size;
	char	**result;
	char	*tmp_result;
	t_env	*tmp;
	int		i;

	size = ft_envlist_size(env);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (NULL);
	i = 0;
	tmp = env;
	while (env)
	{
		tmp_result = ft_strjoin(env->var, "=", cmds->data);
		result[i] = ft_strjoin(tmp_result, env->value, cmds->data);
		free(tmp_result);
		i++;
		env = env->next;
	}
	result[size] = NULL;
	env = tmp;
	return (result);
}

//Function to get the output of the children process
//it wait for the execution of child process and return
//exit status of last command executed in case of pipeline
int	ft_wait_children(t_cmd *cmds)
{
	pid_t	wait_pid;
	t_cmd	*tmp;
	int		status;
	int		result;

	result = 0;
	tmp = cmds;
	while (tmp)
	{
		wait_pid = waitpid(tmp->pid, &status, 0);
		if (wait_pid == -1)
		{
			perror("waitpid");
			break ;
		}
		if (WIFSIGNALED(status))
			result = 128 + WTERMSIG(status);
		else if (WIFEXITED(status))
			result = WEXITSTATUS(status);
		else
			result = status;
		g_exit_status = result;
		tmp = tmp->next;
	}
	return (result);
}

//Function to get the exit status of child process
int	ft_get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

void	ft_close_fds(t_cmd *cmds, t_data *data)
{
	int		size;
	int		i;

	i = 0;
	size = ft_list_size(cmds);
	while (i < size - 1)
	{
		close(data->pipe_fd[i][READ_END]);
		close(data->pipe_fd[i][WRITE_END]);
		i++;
	}
}

//Function to set the file descriptors in pipelines
//duplicate the fd needed and close the unused ones
//
void	ft_set_fd_for_pipes(t_data *data, int pos, int size)
{
	if (pos == 0)
		ft_set_fd_first_command(data, pos);
	else if (pos == size - 1)
		ft_set_fd_last_command(data, pos);
	else if (pos > 0)
		ft_set_fd_middle_command(data, pos);
}
