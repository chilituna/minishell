/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:25:16 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/13 17:57:40 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//split input into an array of strings
//create a linked list lexer that stores the words from the input
//send to function to check for special characters and create tokens
//return the linked list
t_lexer	*ft_lexer(char *input, t_data *data)
{
	int		i;
	t_lexer	*head;
	t_lexer	*tmp;
	t_lexer	*new;

	i = 0;
	while (input[0])
	{
		new = ft_init_lexer(i, data);
		if (i == 0)
			head = new;
		else
		{
			tmp->next = new;
			new->prev = tmp;
		}
		input = ft_pick_string(input, new);
		ft_tokenizer(new);
		tmp = new;
		i++;
	}
	return (head);
}

t_lexer	*ft_init_lexer(int i, t_data *data)
{
	t_lexer	*lexer;

	lexer = ft_malloc(sizeof(t_lexer), data);
	lexer->index = i;
	lexer->str = NULL;
	lexer->token = NULL;
	lexer->next = NULL;
	lexer->prev = NULL;
	lexer->data = data;
	return (lexer);
}

//check for special characters and create tokens:
// - pipes
// - redirections
// - heredoc
void	ft_tokenizer(t_lexer *lexer)
{
	if (!ft_strncmp(lexer->str, "|", 1) && ft_strlen(lexer->str) == 1)
		lexer->token = ft_strdup("PIPE", lexer->data);
	else if (!ft_strncmp(lexer->str, ">", 1) && ft_strlen(lexer->str) == 1)
		lexer->token = ft_strdup("REDIR_OUT", lexer->data);
	else if (!ft_strncmp(lexer->str, ">>", 2) && ft_strlen(lexer->str) == 2)
		lexer->token = ft_strdup("REDIR_APPEND", lexer->data);
	else if (!ft_strncmp(lexer->str, "<", 1) && ft_strlen(lexer->str) == 1)
		lexer->token = ft_strdup("REDIR_IN", lexer->data);
	else if (!ft_strncmp(lexer->str, "<<", 2) && ft_strlen(lexer->str) == 2)
		lexer->token = ft_strdup("REDIR_HEREDOC", lexer->data);
	if (lexer->token)
	{
		free(lexer->str);
		lexer->str = NULL;
	}
}