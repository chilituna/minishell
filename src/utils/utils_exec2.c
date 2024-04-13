/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:39:03 by lperez-h          #+#    #+#             */
/*   Updated: 2024/04/13 14:46:57 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function to set the file descriptor
//of the first command in a pipeline
void	ft_set_fd_first_command(t_data *data, int pos)
{
	//ft_redirect_input(cmd->redir, cmd);
	//still need to check for input and output redirections and duplicate fd accordingly
	if (dup2(data->pipe_fd[pos][WRITE_END], STDOUT_FILENO) == -1)
		ft_error_dup(data);
	// if (close(data->pipe_fd[pos][WRITE_END]) == -1)
	// 	ft_error_closing(data);
}

//Function to set the file descriptors
//of the commands in the middle of the pipeline
//it duplicates and close file descriptors
void	ft_set_fd_middle_command(t_data *data, int pos)
{
	if (dup2(data->pipe_fd[pos - 1][READ_END], STDIN_FILENO) == -1)
		ft_error_dup(data);
	// if (close(data->pipe_fd[pos - 1][READ_END]) == -1)
	// 	ft_error_closing(data);
	if (dup2(data->pipe_fd[pos][WRITE_END], STDOUT_FILENO) == -1)
		ft_error_dup(data);
	// if (close(data->pipe_fd[pos][WRITE_END]) == -1)
	// 	ft_error_closing(data);
}

//function to set the file descriptors
//of the last command in a pipeline
void	ft_set_fd_last_command(t_data *data, int pos)
{
	//still need to check for output redirections
	if (dup2(data->pipe_fd[pos - 1][READ_END], STDIN_FILENO) == -1)
		ft_error_dup(data);
	// if (close(data->pipe_fd[pos - 1][READ_END]) == -1)
	// 	ft_error_closing(data);
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
