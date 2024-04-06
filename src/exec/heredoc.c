/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:23:00 by aarpo e           #+#    #+#             */
/*   Updated: 2024/04/06 15:51:01 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_endofvar(char *line, int i)
{
	while (ft_isalnum(line[i]) || line[i] == '_' || line[i] == '?')
		i++;
	return (i);
}

// check if the line contains $, if it does, expand the env var
// return the expanded line
char	*ft_heredoc_expand(char *line, t_data *data)
{
	char	*tmp_line;
	int		i;
	int		start;
	char	*end_line;
	char	*env;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			tmp_line = ft_substr(line, 0, i, data);
			i++;
			start = i;
			i = ft_endofvar(line, i);
			end_line = ft_substr(line, i, ft_strlen(line) - i, data);
			env = ft_getenv(ft_substr(line, start, i - start, data), data);
			tmp_line = ft_strjoin(tmp_line, env, data);
			line = ft_strjoin(ft_strjoin(tmp_line, env, data), end_line, data);
			ft_freeall_here(tmp_line, end_line, env);
			i = -1;
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

	filename = ft_create_here_doc(data);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	while (1)
	{
		ft_putstr_fd("> ", STDERR_FILENO);
		line = get_next_line(STDIN_FILENO, data);
		if (!ft_strncmp(line, redir->delim, ft_strlen(redir->delim)))
		{
			free(line);
			break ;
		}
		line = ft_heredoc_expand(line, data);
		ft_putstr_fd(line, fd);
		free(line);
	}
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
				ft_putstr_fd("heredoc error ", STDIN_FILENO);
				return ;
			}
		}
		redir = redir->next;
	}
}
