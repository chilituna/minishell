/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:51:42 by luifer            #+#    #+#             */
/*   Updated: 2024/04/13 13:11:57 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function to sort the environment variables alphabetically
void	ft_sort_env_list(t_env *env)
{
	t_env	*tmp;
	char	*var;
	char	*value;

	tmp = env;
	while (tmp)
	{
		if (tmp->next)
		{
			if (ft_strncmp(tmp->var, tmp->next->var,
					ft_strlen(tmp->var)) > 0)
			{
				var = tmp->var;
				value = tmp->value;
				tmp->var = tmp->next->var;
				tmp->value = tmp->next->value;
				tmp->next->var = var;
				tmp->next->value = value;
				tmp = env;
			}
			else
				tmp = tmp->next;
		}
		else
			break ;
	}
}

//function to print the environment variables present at the
// moment of execution. Simple export without arguments.
// the list should be printed alphabetically
int	ft_print_export(t_cmd *cmds)
{
	t_env	*tmp;

	tmp = cmds->data->env;
	ft_sort_env_list(tmp);
	while (tmp)
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

//Function to find the node that contains the specified name
// of the enviroment variable
t_env	*ft_find_env_var(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
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
		{
			name = ft_substr(str, 0, i, data);
			break ;
		}
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
//if export is called without arguments, it will print the environment variables
//not found and must be created
int	ft_export(t_cmd *cmds)
{
	char	*name;
	char	*value;
	t_env	*tmp;

	if (!(cmds->cmd_arg[1]))
	{
		ft_print_export(cmds);
		return (0);
	}
	name = ft_check_input(cmds->cmd_arg[1], cmds->data);
	if (name == NULL)
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(cmds->cmd_arg[1], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		cmds->data->exit_status = 1;
		return (1);
	}
	else
	{
		if (ft_strchr(cmds->cmd_arg[1], '=') == NULL)
			value = NULL;
		else
			value = ft_substr(cmds->cmd_arg[1], ft_strlen(name) + 1,
					ft_strlen(cmds->cmd_arg[1]) - ft_strlen(name) - 1,
					cmds->data);
		tmp = ft_search_env_var(cmds->data->env, name);
		if (tmp == NULL)
		{
			tmp = ft_create_env(name, value);
			ft_add_var_back(cmds->data->env, tmp);
		}
		else if (value)
			ft_update_env_var(name, value, cmds->data);
	}
	cmds->data->exit_status = 0;
	return (0);
}
