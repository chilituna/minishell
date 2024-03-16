/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarpo e  <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:23:00 by aarpo e           #+#    #+#             */
/*   Updated: 2024/03/16 18:27:41 by aarpo e          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_create_here_doc(t_data *data)
{
	static int	i;
	char		*filename;
	char		*tmp;

	tmp = ft_itoa(i++);
	filename = ft_strjoin("heredoc_", tmp, data);
	free(tmp);
	return (filename);
}

// create a temporary file to store the heredoc
void	ft_heredoc(t_redir *redir, t_data *data)
{
	char		*filename;
	int			fd;
	char		*line;

	filename = ft_create_here_doc(data);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("heredoc error ", STDIN_FILENO);
		return ;
	}
	while (1)
	{
		ft_putstr_fd("> ", STDERR_FILENO);
		line = get_next_line(STDIN_FILENO, data);
		if (!ft_strncmp(line, redir->heredoc_delim, ft_strlen(redir->heredoc_delim)))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	redir->in = filename;
	close(fd);
}

// check if redirections include heredoc
void	ft_check_here_doc(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->heredoc)
			ft_heredoc(redir, cmd->data);
		redir = redir->next;
	}
}