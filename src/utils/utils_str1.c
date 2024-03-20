/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:10:45 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/20 14:12:37 by aarponen         ###   ########.fr       */
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


// take a string and return a substring of len length from start
char	*ft_substr(char const *s, unsigned int start, size_t len, t_data *data)
{
	char	*subs;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup("", data));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	subs = ft_malloc(sizeof(char) * (len + 1), data);
	if (subs == NULL)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

// locates the first occurrence of c in the string pointed to by s
// returns a pointer to the located character, or NULL if no match was found.
// the terminating null byte is considered part of the string:
// if c is '\0', the function locates the terminating '\0'.
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
