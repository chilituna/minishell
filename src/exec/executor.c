/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:36:49 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/02 14:18:56 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Convert the environment list into an array
//it iterates through the list joining the variable name
//with their respective value and save each one into the array
//it returns the array once it traverse the whole list.
char	**ft_convert_env_list_to_array(t_env *env, t_cmd *cmds)
{
	int		size;
	char	**result;
	t_env	*tmp;
	int		i;

	size = ft_envlist_size(env);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (NULL);
	i = 0;
	tmp = env;
	while(env)
	{
		result[i] = ft_strjoin(env->var, env->value, cmds->data);
		i++;
		env = env->next;
	}
	result[size] = NULL;
	env = tmp;
	return(result);
}

//Function to execute a single command
//it creates a child process and executes
//the command with the PATH
void	ft_execute_single_command(t_cmd *cmds)
{
	char	*path;
	char	**env;
	pid_t	pid;

	ft_check_here_doc(cmds);
	if (cmds->builtin)
		cmds->builtin(cmds);
	else
	{
		ft_find_cmd_path(cmds, cmds->data);
		path = ft_strdup(cmds->path, cmds->data);
		env = ft_convert_env_list_to_array(cmds->data->env, cmds);
		pid = fork();
		if (pid == 0)
			execve(path, cmds->cmd_arg, env);
		else
		{
			wait(NULL);
			cmds->data->exit_status = 0;
		}
		free(env);
	}
}

//Function to execute the commands received
//as arguments in the shell, the function will check
//for heredocs, builtins and size of list of commands
void	ft_execute_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	//int		pipes;
	int		childs;
	int		i;
	//int		j;

	if (ft_list_size(cmds) == 1)
		ft_execute_single_command(cmds);
	else
	{
		childs = ft_list_size(cmds);
		i = 0;
		tmp = cmds;
		while (tmp)
		{
			ft_set_pipes(cmds);
			ft_create_child_process(cmds);
			ft_set_fd_for_pipe(cmds, tmp);
			ft_close_fd_for_pipe(cmds, tmp);
			ft_execute_single_command(tmp);
			while (i <= childs)//while loop to wait for each child process execution
			{
				wait(NULL);
				i++;
			}
			tmp = tmp->next;
		}
	}
}
