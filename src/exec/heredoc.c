/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:23:00 by aarpo e           #+#    #+#             */
/*   Updated: 2024/03/20 14:02:23 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if the line contains $, if it does, expand the env var
// return the expanded line
char	*ft_heredoc_expand(char *line, t_data *data)
{
	char	*expanded_line;
	int		i;
	int		start;
	char	*end_line;
	char	*env_var;

	i = 0;
	while (line[i])
	{
		if (line [i]== '$')
		{
			expanded_line = ft_substr(line, 0, i, data);
			i++;
			start = i;
			while (ft_isalnum(line[i]) || line[i] == '_' || line[i] == '?')
				i++;
			end_line = ft_substr(line, i, ft_strlen(line) - i, data);
			env_var = ft_get_env_var(ft_substr(line, start, i - start, data), data);
			expanded_line = ft_strjoin(expanded_line, env_var, data);
			expanded_line = ft_strjoin(expanded_line, end_line, data);
			free(line);
			free(end_line);
			free(env_var);
		}
		i++;
	}
	return (expanded_line);
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

