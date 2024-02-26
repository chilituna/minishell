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
void	ft_put_line(int n, char **str, int out)
{
	while (str[n])//while there is a string it will print it
	{
		ft_putstr_fd(str[n++], out);//print the string
		if(str[i])//if there is a new string, print space and keep printing the new one
			ft_putchar_fd(' ', out);
	}
}

int	ft_echo(t_cmd *cmds, t_redir *redir)
{
	int	i;
	int	j;
	int	flag;

	i = 1;//init at 1 to skip program name
	flag = 1;//init as false
	while ((cmds->flags[i] != '\0') && (cmds->flags[i][0] == '-') && (cmds->flags[i][1] == 'n'))//check for flag -n
	{
		j = 1;
		while (cmds->flags[i][j] == 'n')//avoid -nnnn since stay with 1st n found
			j++;
		if (cmds->flags[i][j] == '\0')//
			flag = 0;//true -n found
		else
			break ;//break if there are more chars after -n
		i++;
	}
	ft_put_line(i, cmds->flags, STDOUT_FILENO);
	if (flag == 1)//if n is not found put \n 
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

//-cd ->only relative or absolute path
//-pwd 
//-export
//-unset
//-env ->no options or arguments
//-exit ->no options