/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:45:31 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/06 17:14:38 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// malloc with error check
void	*ft_malloc(size_t size, t_data *data)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		ft_error_and_exit("malloc failed", data);
	return (ptr);
}

// free the array of strings
void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// freeing the 3 strings from heredoc function
void	ft_freeall_here(char *line, char *end_line, char *env_var)
{
	free(line);
	free(end_line);
	free(env_var);
}
