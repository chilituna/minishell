/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:12:37 by lperez-h          #+#    #+#             */
/*   Updated: 2024/02/24 17:17:02 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//-echo -n
static void	ft_put_line(int n, char **str, int out)
{
	while (str[n])
	{
		ft_putstr_fd(str[n++], out);
		
		
	}
}

int	ft_echo(t_cmd *cmds, t_redir *redir)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 1;//false
	while (cmds->flags[i] && cmds->flags[i][0] == '-' && cmds->flags[i][1] == 'n')
	{
		j = 1;
		while (cmds->flags[i][j] == 'n')
			j++;
		if (cmds->flags[i][j] == '\0')
			flag = 0;//true
		else
			break ;
	}
}

//-cd ->only relative or absolute path
//-pwd 
//-export
//-unset
//-env ->no options or arguments
//-exit ->no options