/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:51:42 by luifer            #+#    #+#             */
/*   Updated: 2024/03/17 13:20:11 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function to print the environment variables present at the moment of execution. Simple export without arguments.
int	ft_print_export(t_cmd *cmds)
{
	t_env	*tmp;

	tmp = cmds->data->env;
	while (tmp->next != NULL)
	{
		write(STDOUT_FILENO, "declare -x ", 12);
		ft_putstr_fd(tmp->var, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(tmp->value, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		tmp = tmp->next;
	}
	cmds->data->exit_status = 0;
	return (0);
}

//Function to find the node that contains the specified name of the enviroment variable
t_env	*ft_find_env_var(t_env *env, char *name)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp->next != NULL)
	{
		if (ft_strncmp(tmp->var, name, ft_strlen(name)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_check_input(char *str, t_data *data)
{
	int		i;
	char	*name;
	char	*value;
	char	**input;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			input = ft_split(str, '=');
			name = ft_strdup(input[0], data);
			value = ft_strdup(input[1], data);
			if (ft_all_capitals(name) == 0)
				return (0);
		}
		i++;
	}
	return (1);
}


//creation of new variables and assign of values. This is the actual function
int	ft_export(t_cmd *cmds)
{
	char	**input;
	char	*name;
	char	*value;
	t_env	*tmp;

	tmp = cmds->data->env;
	if (!(cmds->cmd_arg[1]))//if export is called without arguments
		ft_print_export(cmds);
	else if (ft_check_input(cmds->cmd_arg[1], cmds->data) == 1)
	{
		ft_putstr_fd("( Not a valid identifier)", STDERR_FILENO);
		cmds->data->exit_status = 1;
		return (1);
	}
	else
	{
		input = ft_split(cmds->cmd_arg[1], '=');
		name = ft_strdup(input[0], cmds->data);
		value = ft_strdup(input[1], cmds->data);
		tmp = ft_search_env_var(cmds->data->env, name);
		if (tmp == NULL)//not found and must be created
		{
			tmp = ft_create_env(name, value);
			ft_add_var_back(cmds->data->env, tmp);
		}
		else
			ft_update_env_var(name, value, cmds->data);
	}
	cmds->data->exit_status = 0;
	return (0);
}
