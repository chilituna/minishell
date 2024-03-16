/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarpo e  <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 08:42:57 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/16 17:32:52 by aarpo e          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pre_ft_strjoin(char *line, char *temp_buffer, t_data *data)
{
	char	*str;

	if (temp_buffer[0] == '\0' && !line)
	{
		free(temp_buffer);
		return (NULL);
	}
	if (!line)
	{
		line = (char *)malloc(sizeof(char) * 1);
		if (!line)
		{
			free(temp_buffer);
			return (NULL);
		}
		line[0] = '\0';
	}
	str = ft_strjoin(line, temp_buffer, data);
	if (!str)
		free(temp_buffer);
	free(line);
	return (str);
}

char	*go_to_next_line(char *line, t_data *data)
{
	char	*next_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return (NULL);
	}
	while (line[i + j])
		j++;
	next_line = ft_substr(line, i + 1, j, data);
	if (!next_line)
	{
		free(line);
		return (NULL);
	}
	free(line);
	return (next_line);
}

char	*copy_new_line(char *line, t_data *data)
{
	char	*new_line;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	new_line = ft_substr(line, 0, i + 1, data);
	if (!new_line)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	return (new_line);
}

char	*ft_read_line(int fd, char *reading_line, t_data *data)
{
	int		read_bytes;
	char	*temp_buffer;

	temp_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(reading_line, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, temp_buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			if (reading_line)
				free(reading_line);
			free(temp_buffer);
			return (NULL);
		}
		temp_buffer[read_bytes] = '\0';
		reading_line = pre_ft_strjoin(reading_line, temp_buffer, data);
		if (!reading_line)
			return (NULL);
	}
	free(temp_buffer);
	return (reading_line);
}

char	*get_next_line(int fd, t_data *data)
{
	static char	*reading_line;
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reading_line = ft_read_line(fd, reading_line, data);
	if (!reading_line)
		return (NULL);
	if (reading_line[0] == '\0')
	{
		free(reading_line);
		reading_line = NULL;
		return (NULL);
	}
	new_line = copy_new_line(reading_line, data);
	if (!new_line)
		return (NULL);
	reading_line = go_to_next_line(reading_line, data);
	return (new_line);
}
