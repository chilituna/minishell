/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:51:42 by luifer            #+#    #+#             */
/*   Updated: 2024/04/17 19:47:02 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_validate_name(char *name)
{
	int	i;

	i = 0;
	while (name[i] != '\0')
	{
		if (isalnum(name[i]) == 0 && name[i] != '_')
			return (NULL);
		i++;
	}
	return (name);
}

char	*ft_check_input(char *str, t_data *data)
{
	int		i;
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
	i = 0;
	name = ft_validate_name(name);
	return (name);
}

void	ft_export_env_var(char *name, t_cmd *cmds)
{
	t_env	*tmp;
	char	*value;

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

//creation of new variables and assign of values. This is the actual function
//if export is called without arguments, it will print the environment variables
//not found and must be created
int	ft_export(t_cmd *cmds)
{
	char	*name;

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
		ft_export_env_var(name, cmds);
	cmds->data->exit_status = 0;
	return (0);
}
