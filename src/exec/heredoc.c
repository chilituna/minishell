/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:23:00 by aarpo e           #+#    #+#             */
/*   Updated: 2024/04/21 22:26:56 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if the line contains $, if it does, expand the env var
// return the expanded line
char	*ft_heredoc_expand(char *line, t_data *data)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (line[i + 1] && line[i + 1] == '?')
				i = ft_expand_exit_here(&line, i, data);
			else if (ft_isalpha(line[i + 1]) || line[i + 1] == '_')
				i = ft_expand_env_var_here(&line, i, data);
		}
		i++;
	}
	return (line);
}

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
int	ft_heredoc(t_redir *redir, t_data *data)
{
	char		*filename;
	int			fd;
	char		*line;

	line = NULL;
	filename = ft_create_here_doc(data);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	signal(SIGINT, ft_heredoc_handler);
	while (g_signal_nr == -1)
	{
		ft_putstr_fd("> ", STDERR_FILENO);
		line = get_next_line(STDIN_FILENO, data);
		if (!line || !ft_strncmp(line, redir->delim, ft_strlen(redir->delim)))
			break ;
		line = ft_heredoc_expand(line, data);
		ft_putstr_fd(line, fd);
		ft_free_and_null(line, data);
	}
	ft_free_and_null(line, data);
	redir->in = filename;
	close(fd);
	return (0);
}

// check if redirections include heredoc
void	ft_check_here_doc(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->heredoc)
		{
			if (ft_heredoc(redir, cmd->data) == 1)
			{
				ft_putstr_fd(RED"heredoc error "RESET, STDIN_FILENO);
				return ;
			}
		}
		redir = redir->next;
	}
}
