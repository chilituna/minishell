/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 23:09:42 by luifer            #+#    #+#             */
/*   Updated: 2024/02/26 23:48:48 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *cmds, t_redir *redir)
{
	int 	i;
	char	*buf[PATH_MAX];//path_max is a the limit of path len

	getcwd(buf, sizeof(buf));
	ft_putstr_fd(buf, STDOUT_FILENO);//print the buffer with the path
	free(buf);//read about the free when calling getcwd but not 100% sure
}
