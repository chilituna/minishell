/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:13:16 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/20 18:36:16 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

//initialize data struct
void	ft_init_data(char **envp, t_data *data)
{
	data->env = NULL;
	data->lexer = NULL;
	data->cmd = NULL;
	data->prompt = NULL;
	data->pipe_fd = NULL;
	data->exit_status = 0;
	ft_copy_env(envp, data);
	data->envp = NULL;
	ft_print_banner();
}

//create a linked list to store env variables
void	ft_copy_env(char **envp, t_data *data)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (envp[i])
	{
		name = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i], data);
		value = ft_strdup(ft_strchr(envp[i], '=') + 1, data);
		if (i == 0)
			data->env = ft_create_env(name, value);
		else
			ft_add_var_back(data->env, ft_create_env(name, value));
		i++;
	}
}

//if promt is only whitespace, return 1
int	ft_whitespace(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (ft_isspace(prompt[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

// READ - EVALUATE - PRINT - LOOP
// show prompt
// read input from user (readline)
// add input to history (add_history)
// check for unclosed quotes
// split input into an array of strings
// lexer to create a linked list of the input and check for tokens
// parser to create a tree of the input and check for syntax errors
// execute the commands
// free memory
int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = NULL;
	if (argc != 1 || argv[1])
		ft_error_minishell("usage: ./minishell");
	data = malloc(sizeof(t_data));
	if (!data)
		ft_error_and_exit("malloc error", data);
	ft_init_data(envp, data);
	ft_minishell(data);
}

void	ft_minishell(t_data *data)
{
	while (1)
	{
		ft_signals_interactive();
		data->prompt = readline("minishell $ ");
		if (!data->prompt)
			ft_error_and_exit("Exiting minishell", data);
		ft_signals_running();
		if (data->prompt[0] == '\0' || ft_whitespace(data->prompt))
			continue ;
		add_history(data->prompt);
		if (ft_check_quotes(data->prompt))
		{
			data->lexer = ft_lexer(data->prompt, data);
			data->cmd = ft_parser(data->lexer, data);
			if (!ft_check_cmds(data->cmd))
				continue ;
			ft_execute_cmds(data->cmd);
		}
		ft_free_data(data);
	}
}
