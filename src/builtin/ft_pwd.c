/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 23:09:42 by luifer            #+#    #+#             */
/*   Updated: 2024/02/28 15:22:17 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *cmds)
{
	int		i;
	char	*buf[PATH_MAX];//path_max is a the limit of path len

	getcwd(buf, sizeof(buf));
	ft_putstr_fd(buf, STDOUT_FILENO);//print the buffer with the path
	free(buf);//read about the free when calling getcwd but not 100% sure
}