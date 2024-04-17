/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:45:31 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/17 14:47:14 by aarponen         ###   ########.fr       */
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
