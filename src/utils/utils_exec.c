/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 03:49:10 by luifer            #+#    #+#             */
/*   Updated: 2024/04/01 14:43:23 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

//Function to create a pipe for each command node
//it traverse the list and generate a fd with end and write
//end for each command. It returns 0 on success, 1 on failure
int	ft_set_pipes(t_cmd *cmds)
{
	int		fd[2];
	t_cmd	*tmp;

	tmp = cmds;
	while(tmp)
	{
		if (pipe(fd) == -1)
		{
			ft_putstr_fd(RED"minishell: error piping"RESET, STDERR_FILENO);
			cmds->data->exit_status = 1;
			return (1);
		}
		tmp->cmd_fd = fd;
		tmp = tmp->next;
	}
	return (0); 
}

//Function to set the file descriptors 
//in the pipes. It check if the current command is empty for safety
//if there is a previous command it duplicate the read end
//of the pipe and 
//When done it close unused file descriptors
int	ft_set_fd_for_pipe(t_cmd *cmds, t_cmd *current_cmd)
{
	if (!current_cmd)
		cmds->data->exit_status = 1;
	if (current_cmd->prev)
		dup2(current_cmd->prev->cmd_fd[READ_END], STDIN_FILENO);
	if (current_cmd->next)
		dup2(current_cmd->cmd_fd[WRITE_END], STDOUT_FILENO);
	ft_close_fd_for_pipe(cmds, current_cmd);
	return (1);
}

//Function to close the file descriptors
//in the pipes. It receives a command to skip 
//for which the file descriptos will be leaved open
//since it may still need to be processed.
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
int	ft_create_child_process(t_cmd *cmds)
{
	t_cmd	*tmp;
	pid_t	pid;

	tmp = cmds;
	while(tmp)
	{
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd(RED"minishell: error forking"RESET, STDERR_FILENO);
			cmds->data->exit_status = 1;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}


//Function to redirect the input
//it checks if the input redirection is
//present(heredoc included) and duplicate the fd accordingly
//it returns 0 on success, 1 if an error ocurred
int	ft_redirect_input(t_cmd *cmds)
{
	int	open_fd;

	if ((cmds->redir->in) || ((cmds->redir->heredoc) == 1))
	{
		open_fd = open(cmds->redir->in, O_RDONLY);
		if (open_fd == -1)
		{
			ft_putstr_fd(RED"minishell: error opening input file"RESET, STDERR_FILENO);
			cmds->data->exit_status = 1;
			return (1);
		}
		dup2(open_fd, STDIN_FILENO);
	}
	return (0);
}

//Function to redirect the output
//it checks if the output redirection is
//present and duplicate the fd accordingly
//it considers the case of append
int	ft_redirect_output(t_cmd *cmds)
{
	int	write_fd;

	if (cmds->redir->out)
	{
		if (cmds->redir->append == 1)
		{
			write_fd = open(cmds->redir->out, O_APPEND | O_CREAT);
			if (write_fd == -1)
			{
				ft_putstr_fd(RED"minishell: error appending"RESET, STDERR_FILENO);
				cmds->data->exit_status = 1;
			}
			dup2(write_fd, STDOUT_FILENO);
		}
		else
		{
			write_fd = open(cmds->redir->out, O_CREAT | O_WRONLY);
			if (write_fd == -1)
			{
				ft_putstr_fd(RED"minishell: error writing"RESET, STDERR_FILENO);
			}
			dup2(write_fd, STDOUT_FILENO);
		}
	}
	return (1);
}
