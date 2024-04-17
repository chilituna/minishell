/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:10:46 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/17 16:31:36 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check input redirection:
//if the file is not accessible, return 1
//if the file is accessible, return 0
int	ft_check_infile(t_redir *redir, t_cmd *cmds)
{
	if (access(redir->in, R_OK) == -1)
		return (ft_error_file(cmds->data, redir->in));
	return (0);
}

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
			return (ft_error_file(cmds->data, redir->in));
		open_fd = open(redir->in, O_RDONLY);
		if (open_fd == -1)
			return (ft_error_file(cmds->data, redir->in));
		if (dup2(open_fd, STDIN_FILENO) == -1)
			return (ft_error_dup(cmds->data));
		if (close(open_fd) == -1)
			return (ft_error_closing(cmds->data));
		if (redir->heredoc)
			unlink(redir->in);
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
		return (ft_error_file(cmds->data, redir->out));
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
		return (ft_error_file(cmds->data, redir->out));
	if (dup2(write_fd, STDOUT_FILENO) == -1)
		return (ft_error_dup(cmds->data));
	if (close(write_fd) == -1)
		return (ft_error_closing(cmds->data));
	return (0);
}
