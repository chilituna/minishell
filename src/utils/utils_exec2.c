/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:39:03 by lperez-h          #+#    #+#             */
/*   Updated: 2024/04/21 16:20:33 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function to set the file descriptor
//of the first command in a pipeline
void	ft_set_fd_first_command(t_data *data, int pos)
{
	if (dup2(data->pipe_fd[pos][WRITE_END], STDOUT_FILENO) == -1)
		ft_error_dup(data);
}

//Function to set the file descriptors
//of the commands in the middle of the pipeline
//it duplicates and close file descriptors
void	ft_set_fd_middle_command(t_data *data, int pos)
{
	if (dup2(data->pipe_fd[pos - 1][READ_END], STDIN_FILENO) == -1)
		ft_error_dup(data);
	if (dup2(data->pipe_fd[pos][WRITE_END], STDOUT_FILENO) == -1)
		ft_error_dup(data);
}

//function to set the file descriptors
//of the last command in a pipeline
void	ft_set_fd_last_command(t_data *data, int pos)
{
	if (dup2(data->pipe_fd[pos - 1][READ_END], STDIN_FILENO) == -1)
		ft_error_dup(data);
}

//Function to create the pipes needed for the pipeline
//it will generate size - 1 pipes. It first allocates memory
//for the outer array(rows) and then for the inner array (columns)
//when the memory is allocated it creates the pipes and check for
//errors during creation.
int	ft_create_pipes_and_init(t_cmd *cmds)
{
	int	size;
	int	j;

	size = ft_list_size(cmds);
	cmds->data->pipe_fd = ft_malloc(sizeof(int *) * (size - 1), cmds->data);
	j = 0;
	while (j < size - 1)
	{
		cmds->data->pipe_fd[j] = malloc(sizeof(int) * 2);
		if (!cmds->data->pipe_fd[j])
			return (1);
		j++;
	}
	ft_init_and_create_pipe(cmds);
	return (0);
}

void	ft_init_and_create_pipe(t_cmd *cmds)
{
	int	size;
	int	i;
	int	j;

	size = ft_list_size(cmds);
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < 2)
		{
			cmds->data->pipe_fd[i][j] = 100;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < size - 1)
	{
		if (pipe(cmds->data->pipe_fd[i]) == -1)
			ft_error_piping(cmds->data);
		i++;
	}
}
