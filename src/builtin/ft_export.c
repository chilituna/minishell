/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:51:42 by luifer            #+#    #+#             */
/*   Updated: 2024/03/17 17:20:17 by aarponen         ###   ########.fr       */
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
		if (tmp->value)
		{
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(tmp->value, STDOUT_FILENO);
		}
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

char	*ft_check_input(char *str, t_data *data)
{
	int		i;
	int		j;
	char	*name;

	name = NULL;
	i = 0;
	if (!(str[0] >= 65 && str[0] <= 90) && !(str[0] >= 97 && str[0] <= 122))
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			name = ft_substr(str, 0, i, data);
		i++;
	}
	if (!name)
		name = ft_strdup(str, data);
	j = 0;
	while (name[j] != '\0')
	{
		if (isalnum(name[j]) == 0 && name[j] != '_')
			return (NULL);
		j++;
	}
	return (name);
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
	{
		ft_print_export(cmds);
		return (0);
	}
	name = ft_check_input(cmds->cmd_arg[1], cmds->data);
	if (name == NULL)
	{
		ft_putstr_fd(" not a valid identifier", STDERR_FILENO);
		cmds->data->exit_status = 1;
		return (1);
	}
	else
	{
		input = ft_split(cmds->cmd_arg[1], '=');
		name = ft_strdup(input[0], cmds->data);
		if (input[1] == NULL)
			value = NULL;
		else
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