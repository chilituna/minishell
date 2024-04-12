/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:36:49 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/11 23:17:42 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Function to execute a single command in the shell
//it check for redirections, create child process
//and execute command
int	ft_execute_single_command(t_cmd *cmds)
{
	pid_t	pid;

	if (cmds->builtin && (ft_strncmp(cmds->cmd_arg[0], "cd", 2) == 0
			|| ft_strncmp(cmds->cmd_arg[0], "exit", 4) == 0
			|| ft_strncmp(cmds->cmd_arg[0], "export", 6) == 0
			|| ft_strncmp(cmds->cmd_arg[0], "unset", 5) == 0))
	{
		ft_check_pipe_redirections(cmds);
		cmds->builtin(cmds);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (ft_check_pipe_redirections(cmds) == 1)
				exit (1);
			if (cmds->builtin)
			{
				cmds->builtin(cmds);
				exit (cmds->data->exit_status);
			}
			else
			{
				if (ft_find_cmd_path(cmds, cmds->data) == 1)
					exit (1);
				cmds->data->envp = ft_convert_env_list_to_array(cmds->data->env, cmds);
				execve(cmds->path, cmds->cmd_arg, cmds->data->envp);
				ft_error_executing(cmds->data);
			}
		}
		cmds->pid = 0;
		return (ft_wait_children(cmds));
	}
	return (1);
}

//Function to execute a binary command from the system
//it find the path of the command to execute it
//generate an array with env variables to pass to execve function
//and executes the command.
void	ft_exec_cmd(t_cmd *cmds)
{
	char	*path;
	char	**env;

	ft_find_cmd_path(cmds, cmds->data);
	path = ft_strdup(cmds->path, cmds->data);
	env = ft_convert_env_list_to_array(cmds->data->env, cmds);
	execve(path, cmds->cmd_arg, env);
	free(path);
	ft_free_array(env);
	ft_error_executing(cmds->data);
}

//function to execute a child process
//it will create child process and execute command
int	ft_execute_childrens(t_cmd *cmds)
{
	int		size;
	int		i;
	t_cmd	*tmp;
	pid_t	pid;

	size = ft_list_size(cmds);
	i = 0;
	tmp = cmds;
	while (i < size && tmp)
	{
		pid = fork();
		if (pid == -1)
			ft_error_forking(tmp->data);
		else if (pid == 0)
		{
			ft_set_fd_for_pipes(tmp->data, i, size);
			ft_close_fds(tmp, tmp->data);
			ft_exec_cmd(tmp);
		}
		if (tmp)
			tmp->pid = pid;
		i++;
		tmp = tmp->next;
	}
	return (ft_wait_children(cmds));
}

//Function to execute the commands received
//as arguments in the shell, the function will check
//for heredocs, builtins and size of list of commands
int	ft_execute_cmds(t_cmd *cmds)
{
	int	size;
	int	exit_code;

	size = ft_list_size(cmds);
	if (size == 1)
		return (ft_execute_single_command(cmds));
	else
	{
		ft_create_pipes_and_init(cmds);
		exit_code = ft_execute_childrens(cmds);
	}
	cmds->data->exit_status = exit_code;
	return (exit_code);
}

/*
//Function to execute a single command
//it creates a child process and executes
//the command with the PATH
void	ft_execute_single_command(t_cmd *cmds)
{
	pid_t	pid;

	printf("lets go");
	ft_check_here_doc(cmds);
	printf("heredoc cheked");
	if (cmds->redir->in)
		ft_redirect_input(cmds);
	if (cmds->redir->out)
		ft_redirect_output(cmds);
	if (cmds->builtin)
		cmds->builtin(cmds);
	else
	{
		printf("hello");
		pid = fork();
		if (pid == 0)
			ft_exec_cmd(cmds);
		else
		{
			wait(NULL);
			cmds->data->exit_status = 0;
		}
	}
}

//Function to execute commands in a pipeline
//it iterates through the list of commands and
//creates a child process for each command and
//executes a command inside the child process
void	ft_pipes(t_cmd *cmds)
{
	t_cmd	*tmp;
	pid_t	pid;
	int		size;
	int		i;

	size = ft_list_size(cmds);
	i = 0;
	tmp = cmds;
	while (i < size)
	{
		if ((i < size - 1) && (pipe(cmds->data->pipe_fd[i]) == -1))
			ft_error_piping(cmds->data);
		pid = fork();
		if (pid == -1)
			ft_error_forking(cmds->data);
		else if (pid == 0)
		{

		}

	}

}

*/