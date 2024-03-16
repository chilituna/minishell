/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:45:31 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/16 23:32:29 by lperez-h         ###   ########.fr       */
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

//Function to search and environment variable by
//the name. It returns a pointer to the node containing
//the environment variable if found, else it returns Null.
t_env	*ft_search_env_var(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
	{
		if (ft_strncmp(tmp->var, name, ft_strlen(name)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

//Function to search a enviroment variable and unset it
//it delete in place the linked list when found
void	ft_delete_env_var(t_env *env, char *name)
{
	t_env	*tmp;
	t_env	*to_remove;

	tmp = env;
	while (tmp->next)
	{
		if(ft_strncmp(tmp->var, name, ft_strlen(name)) == 0)//check if is the 1st element in list
		{
			to_remove = tmp;
			tmp = tmp->next;
			free(to_remove);
			return ;
		}
		else if (ft_strncmp(tmp->next->var, name, ft_strlen(name)) == 0)
		{
			to_remove = tmp->next;
			tmp->next = tmp->next->next;
			free(to_remove);
			return ;
		}
		tmp = tmp->next;
	}
}
