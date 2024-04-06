/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 03:49:10 by luifer            #+#    #+#             */
/*   Updated: 2024/04/06 20:57:52 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Function to create a pipe for each command node
//it traverse the list and generate a fd with read and write
//end for each command except for the last one (stdout or redirect).
//It returns 0 on success, 1 on failure
void	ft_set_cmds_pipes_fd(t_cmd *cmds)
{
	int		fd[2];
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (tmp->next == NULL)
			break ;
		if (pipe(fd) == -1)
			ft_error_piping(cmds->data);
		tmp->cmd_fd = fd;
		tmp = tmp->next;
	}
}

//Function to get the output of the children process
//it wait for the execution of child process and return
//exit status of last command executed in case of pipeline
int	ft_wait_children(pid_t pid)
{
	pid_t	wait_pid;
	int		status;
	int		result;

	result = 0;
	wait_pid = 0;
	while (wait_pid != -1 || errno != ECHILD)
	{
		wait_pid = waitpid(-1, &status, 0);
		if (wait_pid == pid)
			result = status;
		continue ;
	}
	if (WIFSIGNALED(result))
		status = 128 + WTERMSIG(result);
	else if (WIFEXITED(result))
		status = WEXITSTATUS(result);
	else
		status = result;
	return (status);
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
		if (dup2(cmds->cmd_fd[READ_END], STDIN_FILENO) == -1)
			ft_error_dup(cmds->data);
		if (dup2(cmds->cmd_fd[WRITE_END], STDOUT_FILENO) == -1)
			ft_error_dup(cmds->data);
		if (close(cmds->cmd_fd[READ_END]) == -1)
			ft_error_closing(cmds->data);
		if (close(cmds->cmd_fd[WRITE_END]) == -1)
			ft_error_closing(cmds->data);
	}
	else if (cmds->prev == NULL)
	{
		if (dup2(cmds->cmd_fd[WRITE_END], STDOUT_FILENO) == -1)
			ft_error_dup(cmds->data);
		if (close(cmds->cmd_fd[WRITE_END]) == -1)
			ft_error_closing(cmds->data);
	}
	if (cmds->next == NULL)
	{
		if (dup2(cmds->cmd_fd[WRITE_END], STDOUT_FILENO) == -1)
			ft_error_dup(cmds->data);
		if (close(cmds->cmd_fd[WRITE_END]) == -1)
			ft_error_closing(cmds->data);
	}
}

//Function to get the exit status of child process
int	ft_get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
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
		if (tmp != skip_cmd && tmp->cmd_fd)
		{
			close(tmp->cmd_fd[READ_END]);
			close(tmp->cmd_fd[WRITE_END]);
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
	if ((dup2(cmds->cmd_fd[WRITE_END], STDOUT_FILENO) == -1))
		ft_error_dup(cmds->data);
	if (close(cmds->cmd_fd[READ_END]) == -1 
		|| close(cmds->cmd_fd[WRITE_END]) == -1)
		ft_error_closing(cmds->data);
	ft_exec_cmd(cmds);
	//return (ft_wait_children(cmds));
}

*/