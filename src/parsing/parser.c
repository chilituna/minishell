/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:46:01 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/26 00:16:09 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// group nodes together based on tokens:
// each group becomes command
// first loop through lexer until a pipe is found
// take all nodes before pipe and group them together in a cmd node
// if no (further) pipes are found, take all nodes until the end of the list
// for each command, check for redirections
// create a redirection node for each:
// (token and filename or delimeter if heredoc)
// remove the redirection nodes from lexer
// check if command is a builtin and store a function pointer
// to the corresponding function
// combine remaining words into **char for execve


// calculate how many pipes are in the input
// return the number of pipes + 1,
// which is the number of commands
int	ft_check_pipes(t_lexer *lexer)
{
	int		pipes;
	t_lexer	*temp;

	pipes = 0;
	temp = lexer;
	while (temp)
	{
		if (temp->token)
		{
			if (ft_strncmp(temp->token, "PIPE", 4) == 0)
				pipes++;
		}
		temp = temp->next;
	}
	return (pipes + 1);
}

// calculate pipes and create a linked list of commands:
// if no pipes, create a single command node
// if there is 1 pipe, create 2 command nodes etc...
// initialize each command node
// create an array of tokens for each command node
// return the head of the command linked list
t_cmd	*ft_parser(t_lexer *lexer, t_data *data)
{
	int		i;
	int		pipes;
	t_cmd	*head;
	t_cmd	*tmp;
	t_cmd	*new;

	i = 0;
	pipes = ft_check_pipes(lexer);
	while (i < pipes)
	{
		new = ft_init_cmd(new, i, data);
		lexer = ft_create_cmd(lexer, new);
		if (i == 0)
			head = new;
		else
		{
			tmp->next = new;
			new->prev = tmp;
		}
		tmp = new;
		i++;
	}
	tmp = NULL;
	return (head);
}

t_cmd	*ft_init_cmd(t_cmd *cmd, int i, t_data *data)
{
	cmd = ft_malloc(sizeof(t_cmd), data);
	cmd->index = i;
	cmd->tokens = NULL;
	cmd->flags = NULL;
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->data = data;
	return (cmd);
}


// copy all lexer nodes before a pipe in the command node 2D array (tokens)
// continue until the end of the list
// remove the nodes from the lexer
// return the new head of the lexer
t_lexer	*ft_create_cmd(t_lexer *lexer, t_cmd *cmd)
{
	int		i;
	t_lexer	*temp;

	i = 0;
	temp = lexer;
	cmd->tokens = ft_malloc(sizeof(char *) * (ft_count_tokens(lexer) + 1),
			cmd->data);
	while (temp)
	{
		if (temp->token)
		{
			if (ft_strncmp(temp->token, "PIPE", 4) == 0)
			{
				lexer = temp->next;
				break ;
			}
			cmd->tokens[i] = ft_strdup(temp->token, cmd->data);
		}
		else
			cmd->tokens[i] = ft_strdup(temp->str, cmd->data);
		i++;
		temp = temp->next;
	}
	cmd->tokens[i] = NULL;
	return (lexer);
}

// count the number of tokens in the lexer before a pipe
// return the number of tokens
int	ft_count_tokens(t_lexer *lexer)
{
	int		i;
	t_lexer	*temp;

	i = 0;
	temp = lexer;
	while (temp)
	{
		if (temp->token)
		{
			if (ft_strncmp(temp->token, "PIPE", 4) == 0)
				break ;
		}
		i++;
		temp = temp->next;
	}
	return (i);
}



