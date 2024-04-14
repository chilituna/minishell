/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:34:50 by lperez-h          #+#    #+#             */
/*   Updated: 2024/04/14 13:28:09 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Function to redirect the input
//it checks if the input redirection is
//present(heredoc included) and duplicate the fd accordingly
//it returns 0 on success, 1 if an error ocurred
int	ft_redirect_input(t_redir *redir, t_cmd *cmds)
{
	int	open_fd;

	if (redir->in)
	{
		if (access(redir->in, R_OK) == -1)
			return (ft_error_opening(cmds->data, redir->in));
		open_fd = open(redir->in, O_RDONLY);
		if (open_fd == -1)
			return (ft_error_opening(cmds->data, redir->in));
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
int	ft_check_outfile(t_redir *redir, t_cmd *cmds)
{
	int	write_fd;

	if (redir->append == 1)
		write_fd = open(redir->out, O_WRONLY | O_APPEND | O_CREAT, 0664);
	else
		write_fd = open(redir->out, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (write_fd == -1)
		return (ft_error_writing(cmds->data, redir->out));
	return (0);
}

//check input redirection:
//if the file is not accessible, return 1
//if the file is accessible, return 0
int	ft_check_infile(t_redir *redir, t_cmd *cmds)
{
	if (access(redir->in, R_OK) == -1)
		return (ft_error_opening(cmds->data, redir->in));
	return (0);
}

int	ft_redirect_output(t_redir *redir, t_cmd *cmds)
{
	int	write_fd;

	if (redir->append == 1)
		write_fd = open(redir->out, O_WRONLY | O_APPEND | O_CREAT, 0664);
	else
		write_fd = open(redir->out, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (write_fd == -1)
		return (ft_error_writing(cmds->data, redir->out));
	if (dup2(write_fd, STDOUT_FILENO) == -1)
		return (ft_error_dup(cmds->data));
	if (close(write_fd) == -1)
		return (ft_error_closing(cmds->data));
	return (0);
}

//Function to check pipeline redirections
//it will iterate the command list and the
//redirection list. For each command it will
//iterate the corresponding redir list
//for input the last redir struct will be checked
//for output all redir structs will be checked
int	ft_handle_redirs(t_cmd *cmds)
{
	t_cmd	*tmp;
	t_redir	*tmp_redir;
	t_redir	*last_i;
	t_redir	*last_o;

	last_i = NULL;
	last_o = NULL;
	tmp = cmds;
	ft_check_here_doc(tmp);
	tmp_redir = tmp->redir;
	while (tmp_redir)
	{
		if (tmp_redir->in)
		{
			if (ft_check_infile(tmp_redir, tmp) == 1)
				return (1);
			last_i = tmp_redir;
		}
		if (tmp_redir->out)
		{
			if (ft_check_outfile(tmp_redir, tmp) == 1)
				return (1);
			last_o = tmp_redir;
		}
		tmp_redir = tmp_redir->next;

	}
	if (last_i)
	{
		if (ft_redirect_input(last_i, tmp) == 1)
			return (1);
	}
	if (last_o)
	{
		if (ft_redirect_output(last_o, tmp) == 1)
			return (1);
	}
	return (0);
}

