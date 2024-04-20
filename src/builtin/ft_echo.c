/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:12:37 by lperez-h          #+#    #+#             */
/*   Updated: 2024/04/20 18:19:59 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//while there is a string it will print it
//if there is a new string, print space and keep printing the new one
void	ft_put_line(int n, char **str, int out)
{
	while (str[n])
	{
		if (str[n][0] != '\0')
		{
			ft_putstr_fd(str[n], out);
			if (str[++n])
				ft_putchar_fd(' ', out);
		}
		else
			n++;
	}
}

int	ft_new_line(int out)
{
	ft_putchar_fd('\n', out);
	return (EXIT_SUCCESS);
}

//-echo -n
//init at 1 to skip program name
//if there are no arguments to cd print a new line and return prompt to user
//if there is a -n flag, print the line without a new line
//avoid -nnnn since stay with 1st n found
//break if there are more chars after -n
//if n is not found put \n
int	ft_echo(t_cmd *cmds)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 1;
	if (!(cmds->cmd_arg[1]))
		return (ft_new_line(STDOUT_FILENO));
	if ((cmds->cmd_arg[1][0] == '-') && (cmds->cmd_arg[1][1] == 'n'))
	{
		j = 1;
		while (cmds->cmd_arg[i][j] == 'n')
			j++;
		if (cmds->cmd_arg[i][j] == '\0')
			flag = 0;
		i++;
	}
	if (cmds->cmd_arg[i])
		ft_put_line(i, cmds->cmd_arg, STDOUT_FILENO);
	if (flag == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	cmds->data->exit_status = 0;
	return (EXIT_SUCCESS);
}
