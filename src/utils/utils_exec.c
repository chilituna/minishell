/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 03:49:10 by luifer            #+#    #+#             */
/*   Updated: 2024/04/10 23:11:31 by luifer           ###   ########.fr       */
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
		result[i] = ft_strjoin(env->var, env->value, cmds->data);
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
	wait_pid = 0;
	tmp = cmds;
	while (tmp && errno != ECHILD)
	{
		wait_pid = waitpid(tmp->pid, &status, 0);
		if (wait_pid == tmp->pid)
			result = status;
		tmp = tmp->next;
	}
	if (WIFSIGNALED(result))
		status = 128 + WTERMSIG(result);
	else if (WIFEXITED(result))
		status = WEXITSTATUS(result);
	else
		status = result;
	return (status);
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

//Function to create the pipes needed for the pipeline
//it will generate size - 1 pipes. It first allocates memory
//for the outer array(rows) and then for the inner array (columns)
//when the memory is allocated it creates the pipes and check for 
//errors during creation.
int	ft_set_pipes_fd(t_cmd *cmds)
{
	int	size;
	int	i;
	int	j;

	size = ft_list_size(cmds);
	i = 0;
	cmds->data->pipe_fd = malloc(sizeof(int *) * (size - 1));//outer array
	if (!cmds->data->pipe_fd)
		return (1);//ft_error_malloc?
	while(j < size - 1)
	{
		cmds->data->pipe_fd[j] = malloc(sizeof(int) * 2);
		if (!cmds->data->pipe_fd[j])
			return (1);
		j++;
	}
	while (i < size - 1)
	{
		if (pipe(cmds->data->pipe_fd[i]) == -1)
			ft_error_piping(cmds->data);
		i++;
	}
	return (0);
}

/*
//Function to close the file descriptors
//in the pipes. It receives a command to skip
//the child specify it's own command to skip, in order
//to not close it's own fd
void	ft_close_fd_for_pipe(t_cmd *cmds, t_cmd *skip_cmd)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (tmp != skip_cmd && tmp->pipe_fd)
		{
			close(tmp->pipe_fd[READ_END]);
			close(tmp->pipe_fd[WRITE_END]);
		}
		tmp = tmp->next;
	}
}

//Function to create a child process for each command
//in the command list, it will make a fork call
//for each command. It returns 1 on error, 0 on success
int	ft_execute_child(t_cmd *cmds)
{
	(void)pid;
	if ((dup2(cmds->pipe_fd[WRITE_END], STDOUT_FILENO) == -1))
		ft_error_dup(cmds->data);
	if (close(cmds->pipe_fd[READ_END]) == -1
		|| close(cmds->pipe_fd[WRITE_END]) == -1)
		ft_error_closing(cmds->data);
	ft_exec_cmd(cmds);
	//return (ft_wait_children(cmds));
}


//Function to set the file descriptors
//in the pipes. It check if the current command is empty for safety
//if there is a previous command it duplicate the read end
//of the pipe to receive input. If there is a next command it duplicate the
//write end of the pipe to send output. In case both are present (next + prev)
//duplicate both. When done it close unused file descriptors
void	ft_dup_fd_for_pipe(t_cmd *cmds)
{
	if (cmds->prev && cmds->next)
	{
		if (dup2(cmds->data->pipe_fd[READ_END], STDIN_FILENO) == -1)
			ft_error_dup(cmds->data);
		if (dup2(cmds->data->pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
			ft_error_dup(cmds->data);
		if (close(cmds->data->pipe_fd[READ_END]) == -1)
			ft_error_closing(cmds->data);
		if (close(cmds->data->pipe_fd[WRITE_END]) == -1)
			ft_error_closing(cmds->data);
	}
	else if (cmds->prev == NULL)
	{
		if (dup2(cmds->data->pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
			ft_error_dup(cmds->data);
		if (close(cmds->data->pipe_fd[WRITE_END]) == -1)
			ft_error_closing(cmds->data);
	}
	if (cmds->next == NULL)
	{
		if (dup2(cmds->data->pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
			ft_error_dup(cmds->data);
		if (close(cmds->data->pipe_fd[WRITE_END]) == -1)
			ft_error_closing(cmds->data);
	}
}

*/