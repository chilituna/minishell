/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:12:37 by lperez-h          #+#    #+#             */
/*   Updated: 2024/03/14 15:52:44 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//-echo -n
void	ft_put_line(int n, char **str, int out)
{
	while (str[n])//while there is a string it will print it
	{
		ft_putstr_fd(str[n++], out);//print the string
		if(str[n])//if there is a new string, print space and keep printing the new one
			ft_putchar_fd(' ', out);
	}
}

int	ft_echo(t_cmd *cmds)
{
	int	i;
	int	j;
	int	flag;

	i = 1;//init at 1 to skip program name
	flag = 1;//init as false
	if(!(cmds->cmd_arg[1]))//if there are no arguments to cd print a new line and return prompt to user
	{
		write(1, "\n", 1);
		return (0);
	}
	while ((cmds->cmd_arg[i][0] != '\0') && (cmds->cmd_arg[i][0] == '-') && (cmds->cmd_arg[i][1] == 'n'))//check for flag -n
	{
		j = 1;
		while (cmds->cmd_arg[i][j] == 'n')//avoid -nnnn since stay with 1st n found
			j++;
		if (cmds->cmd_arg[i][j] == '\0')//
			flag = 0;//true -n found
		else
			break ;//break if there are more chars after -n
		i++;
	}
	ft_put_line(i, cmds->cmd_arg, STDOUT_FILENO);
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
