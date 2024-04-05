/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:36:49 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/04 19:15:13 by lperez-h         ###   ########.fr       */
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

//Function to execute a single command
//it creates a child process and executes
//the command with the PATH
void	ft_execute_single_command(t_cmd *cmds)
{
	char	*path;
	char	**env;
	pid_t	pid;

	ft_check_here_doc(cmds);
	if (cmds->builtin)
		cmds->builtin(cmds);
	else
	{
		ft_find_cmd_path(cmds, cmds->data);
		path = ft_strdup(cmds->path, cmds->data);
		env = ft_convert_env_list_to_array(cmds->data->env, cmds);
		pid = fork();
		if (pid == 0)
			execve(path, cmds->cmd_arg, env);
		else
		{
			wait(NULL);
			cmds->data->exit_status = 0;
		}
		free(env);
		free(path);
	}
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
	ft_error_cmd(cmds->data);
	return ;
}

//Function to execute commands in a pipeline
//it receives a command and creates a child process 
//for it, duplicate the file descriptor and 
//close the fd not used. It executes the command in the child
//process and the parent process wait for the output and duplicate 
//and close the unused fd in the parent process.
void	ft_pipe(t_cmd *cmds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error_forking(cmds->data);
	if (pid == 0)
	{
		if ((dup2(cmds->cmd_fd[WRITE_END], STDOUT_FILENO) == -1) || close(cmds->cmd_fd[WRITE_END]) == -1 || close(cmds->cmd_fd[READ_END]) == -1)
			ft_error_fd(cmds->data);
		ft_exec_cmd(cmds);
	}
	waitpid(pid, NULL, 0);
	if (dup2(cmds->cmd_fd[READ_END], STDERR_FILENO) == -1 || close(cmds->cmd_fd[READ_END]) == -1 || close(cmds->cmd_fd[WRITE_END]) == -1)
		ft_error_fd(cmds->data);
	return ;
}


//Function to execute the commands received
//as arguments in the shell, the function will check
//for heredocs, builtins and size of list of commands
void	ft_execute_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		size;
	int		i;


	size = ft_list_size(cmds);
	if (size == 1)
		ft_execute_single_command(cmds);
	else
	{
		tmp = cmds;
		while (tmp)
		{
			//ft_set_pipes(cmds);
			ft_create_child_process(cmds);
			ft_set_fd_for_pipe(cmds, tmp);
			ft_close_fd_for_pipe(cmds, tmp);
			ft_execute_single_command(tmp);
			while (i <= childs)//while loop to wait for each child process execution
			{
				wait(NULL);
				i++;
			}
			tmp = tmp->next;
		}
	}
}
