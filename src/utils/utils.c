/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:45:31 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/10 12:11:35 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	int	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
	{
		ft_putchar_fd(*str, fd);
		str++;
	}
}

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	c;

	c = 0;
	while (s1[c] == s2[c] && s1[c] && s2[c] && c < n)
		c++;
	if (c == n)
		return (0);
	return ((unsigned char)s1[c] - (unsigned char)s2[c]);
}

char	*ft_strdup(const char *s, t_data *data)
{
	char		*new_s;
	size_t		len;
	size_t		i;

	len = ft_strlen(s);
	new_s = ft_malloc((len +1) * sizeof(char), data);
	if (new_s == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
