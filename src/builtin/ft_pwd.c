/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 23:09:42 by luifer            #+#    #+#             */
/*   Updated: 2024/03/09 23:25:02 by luifer           ###   ########.fr       */
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
