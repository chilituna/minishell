/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarpo e  <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:13:16 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/13 14:29:49 by aarpo e          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf(BLUE1 "COMMAND: %d\n" RESET, cmd->index + 1);
	while (cmd->cmd_arg[i])
	{
		printf("%s\n", cmd->cmd_arg[i]);
		i++;
	}
	if (cmd->in)
		printf(BLUE3 "IN: %s\n" RESET, cmd->in);
	if (cmd->out)
		printf(BLUE3 "OUT: %s\n" RESET, cmd->out);
}

void	ft_print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s\n", tmp->env);
		tmp = tmp->next;
	}
}

//initialize data struct
void	ft_init_data(char **envp, t_data *data)
{
	data->env = NULL;
	data->lexer = NULL;
	data->cmd = NULL;
	data->prompt = NULL;
	data->exit_status = 0;
	data->env = ft_env(envp, data);
	// ft_print_banner();
}

//create a linked list to store env variables
t_env	*ft_env(char **envp, t_data *data)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		tmp = malloc(sizeof(t_env));
		if (!tmp)
			ft_error_and_exit("malloc error", NULL);
		tmp->env = ft_strdup(envp[i], data);
		tmp->next = env;
		env = tmp;
		i++;
	}
	// ft_print_env(env);
	return (env);
}

// READ
// EVALUATE
// PRINT
// LOOP
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
	while (1)
	{
		ft_signals_interactive();
		data->prompt = readline("minishell $ ");
		if (!data->prompt)
			ft_error_and_exit("Exiting minishell", data);
		ft_signals_running();
		if (data->prompt[0] != '\0')
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
	free(data);
	return (0);
}
