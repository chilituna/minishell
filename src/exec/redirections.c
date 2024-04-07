/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:34:50 by lperez-h          #+#    #+#             */
/*   Updated: 2024/04/07 13:57:54 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Function to redirect the input
//it checks if the input redirection is
//present(heredoc included) and duplicate the fd accordingly
//it returns 0 on success, 1 if an error ocurred
int	ft_redirect_input(t_cmd *cmds)
{
	int	open_fd;

	ft_check_here_doc(cmds);
	if (cmds->redir->in)
	{
		if (access(cmds->redir->in, R_OK) == -1)
			return (ft_error_opening(cmds->data));
		open_fd = open(cmds->redir->in, O_RDONLY);
		if (open_fd == -1)
			return (ft_error_opening(cmds->data));
		if (dup2(open_fd, STDIN_FILENO) == -1)
			return (ft_error_dup(cmds->data));
		if (close(open_fd) == -1)
			return (ft_error_closing(cmds->data));
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

	if (cmds->redir->out && cmds->redir->append == 1)
	{
		write_fd = open(cmds->redir->out, O_APPEND | O_CREAT);
		if (write_fd == -1)
			return (ft_error_writing(cmds->data));
		if (dup2(write_fd, STDOUT_FILENO) == -1)
			return (ft_error_dup(cmds->data));
		if (close(write_fd) == -1)
			return (ft_error_closing(cmds->data));
	}
	else if (cmds->redir->out)
	{
		write_fd = open(cmds->redir->out, O_CREAT | O_WRONLY);
		if (write_fd == -1)
			return (ft_error_writing(cmds->data));
		if (dup2(write_fd, STDOUT_FILENO) == -1)
			return (ft_error_dup(cmds->data));
		if (close(write_fd) == -1)
			return (ft_error_closing(cmds->data));
	}
	return (0);
}

//Function to check pipeline redirections
//it will iterate the command list and the
//redirection list. For each command it will
//iterate the corresponding redir list and check
//for input or output redirection
int	ft_check_pipe_redirections(t_cmd *cmds)
{
	t_cmd	*tmp;
	t_redir	*tmp_redir;

	tmp = cmds;
	while (tmp)
	{
		tmp_redir = tmp->redir;
		while (tmp_redir)
		{
			if (tmp_redir->in)
			{
				if (ft_redirect_input(tmp) == 1)
					return (1);
			}
			if (tmp_redir->out)
				ft_redirect_output(tmp);
			tmp_redir = tmp_redir->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

