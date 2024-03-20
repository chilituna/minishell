/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 23:09:42 by luifer            #+#    #+#             */
/*   Updated: 2024/03/17 18:36:33 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//print the buffer with the path
//path_max is a the limit of path len
//TO DO: free(buf);//read about the free when calling getcwd but not 100% sure
int	ft_pwd(t_cmd *cmds)
{
	char	buf[PATH_MAX];

	(void)cmds;
	getcwd(buf, sizeof(buf));
	ft_putstr_fd(buf, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
