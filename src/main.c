/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:13:16 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/13 22:26:18 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_cmd(t_cmd *cmd)
{
	int		i;
	t_redir	*tmp;

	i = 0;
	printf(BLUE1 "COMMAND: %d\n" RESET, i);
	while (cmd->cmd_arg[i])
	{
		printf("%s\n", cmd->cmd_arg[i]);
		i++;
	}
	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->in)
			printf("redir_in: %s\n", tmp->in);
		if (tmp->out)
			printf("redir_out: %s\n", tmp->out);
		if (tmp->append)
			printf("redir will be appended\n");
		if (tmp->heredoc)
			printf("heredoc\n");
		if (tmp->delim)
			printf("heredoc_delim: %s\n", tmp->delim);
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
	data->pipe_fd = NULL;
	data->exit_status = 0;
	ft_copy_env(envp, data);
	data->envp = NULL;
	// ft_print_banner();
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
	// if (argc != 1 || argv[1])
	// 	ft_error_minishell("usage: ./minishell");
	data = malloc(sizeof(t_data));
	if (!data)
		ft_error_and_exit("malloc error", data);
	ft_init_data(envp, data);
	if (argc > 1 && strcmp(argv[1], "-c") == 0 && argc >= 3)
	{
		data->prompt = ft_strdup(argv[2], data);
		if (ft_check_quotes(data->prompt))
		{
			data->lexer = ft_lexer(data->prompt, data);
			data->cmd = ft_parser(data->lexer, data);
			if (!ft_check_cmds(data->cmd))
				return (data->exit_status);
			ft_execute_cmds(data->cmd);
		}
		ft_free_data(data);
		free(data);
		return (data->exit_status);
	}
	else
	{
		while (1)
		{
			ft_signals_interactive();
			data->prompt = readline("minishell $ ");
			if (!data->prompt)
				ft_error_and_exit("Exiting minishell", data);
			ft_signals_running();
			if (data->prompt[0] == '\0')
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
}
