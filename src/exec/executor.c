/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:36:49 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/20 14:45:20 by lperez-h         ###   ########.fr       */
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
		ft_handle_redirs(cmds);
		cmds->builtin(cmds);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (ft_handle_redirs(cmds) == 1)
				ft_exit_minishell(cmds->data);
			ft_exec_cmd(cmds);
		}
		cmds->pid = pid;
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
	if (cmds->builtin)
	{
		cmds->builtin(cmds);
		ft_exit_minishell(cmds->data);
	}
	else
	{
		if (!cmds->cmd_arg[0])
		{
			g_exit_status = 0;
			ft_exit_minishell(cmds->data);
		}
		if (ft_find_cmd_path(cmds, cmds->data) == 1)
			ft_exit_minishell(cmds->data);
		cmds->data->envp = ft_convert_env_list_to_array(cmds->data->env, cmds);
		execve(cmds->path, cmds->cmd_arg, cmds->data->envp);
		ft_error_executing(cmds->data);
	}
}

void	ft_execute_child(t_cmd *cmds, t_cmd *tmp, int i, int size)
{
	ft_set_fd_for_pipes(tmp->data, i, size);
	if (ft_handle_redirs(tmp) == 1)
		ft_exit_minishell(tmp->data);
	ft_close_fds(cmds, tmp->data);
	ft_exec_cmd(tmp);
}

//function to execute a child process
//it will create child process and execute command
int	ft_execute_children(t_cmd *cmds)
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
			ft_error_forking();
		else if (pid == 0)
			ft_execute_child(cmds, tmp, i, size);
		if (tmp)
			tmp->pid = pid;
		i++;
		tmp = tmp->next;
	}
	ft_close_fds(cmds, cmds->data);
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
		exit_code = ft_execute_children(cmds);
	}
	g_exit_status = exit_code;
	return (exit_code);
}
