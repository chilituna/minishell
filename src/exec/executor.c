/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:36:49 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/07 14:22:18 by aarponen         ###   ########.fr       */
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

void	ft_execute_single_command(t_cmd *cmds)
{
	char	*path;
	char	**env;
	pid_t	pid;

	if (cmds->builtin)
	{
		ft_check_pipe_redirections(cmds);
		cmds->builtin(cmds);
	}
	else
	{
		ft_find_cmd_path(cmds, cmds->data);
		path = ft_strdup(cmds->path, cmds->data);
		env = ft_convert_env_list_to_array(cmds->data->env, cmds);
		pid = fork();
		if (pid == 0)
		{
			if (ft_check_pipe_redirections(cmds) == 1)
				exit (1);
			execve(path, cmds->cmd_arg, env);
			ft_error_executing(cmds->data);
		}
		waitpid(pid, NULL, 0);
		cmds->data->exit_status = 0;
		ft_free_array(env);
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
	free(path);
	free(env);
	ft_error_executing(cmds->data);
}

//Function to execute commands in a pipeline
//it iterates through the list of commands and
//creates a child process for each command and
//executes a command inside the child process
void	ft_pipe(t_cmd *cmds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error_forking(cmds->data);
	if (pid == 0)
		ft_exec_cmd(cmds);
	//else
	//{
	//	waitpid(pid, NULL, 0);
	//	return ;
	//}
}

//Function to execute the commands received
//as arguments in the shell, the function will check
//for heredocs, builtins and size of list of commands
int	ft_execute_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		size;
	pid_t	pid;

	size = ft_list_size(cmds);
	if (size == 1)
		ft_execute_single_command(cmds);
	else
	{
		tmp = cmds;
		ft_set_cmds_pipes_fd(tmp);
		if (ft_strncmp(tmp->cmd_arg[0], "cd", 2) == 0)
			cmds->builtin(tmp);
		while (tmp)
		{
			pid = fork();
			if (pid == -1)
				ft_error_forking(cmds->data);
			if (pid == 0)
			{
				ft_check_pipe_redirections(tmp);
				ft_dup_fd_for_pipe(tmp);
				ft_exec_cmd(tmp);
			}
			tmp = tmp->next;
		}
		return (ft_wait_children(pid));
	}
	return (0);
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
*/