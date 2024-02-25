/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:25:16 by aarpo e           #+#    #+#             */
/*   Updated: 2024/02/25 11:14:33 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// break the input into strings:
// skip whitespace
// put quoted text into a single string
// otherwise, split by space
// create a string and store in a linked list
// return the remaining input
char	*ft_pick_string(char *str, t_lexer *lexer)
{
	int		start;
	int		i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	start = i;
	if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'')
			i++;
		i++;
	}
	else if (str[i] == '\"')
	{
		i++;
		while (str[i] != '\"')
			i++;
		i++;
	}
	else
	{
		while (!ft_isspace(str[i]) && str[i] != '\0')
			i++;
	}
	lexer->str = ft_substr(str, start, i - start);
	return (str + i);
}

//split input into an array of strings
//create a linked list lexer that stores the words from the input
//send to function to check for special characters and create tokens
//return the linked list
t_lexer	*ft_lexer(char *input)
{
	int		i;
	t_lexer	*head;
	t_lexer	*tmp;
	t_lexer	*new;

	i = 0;
	while (input[0] && input[0] != '\n')
	{
		new = ft_init_lexer(new, i);
		input = ft_pick_string(input, new);
		ft_tokenizer(new);
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
	return (head);
}

t_lexer	*ft_init_lexer(t_lexer *lexer, int i)
{
	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		exit(1); // malloc_error function to free memory and exit
	lexer->index = i;
	lexer->str = NULL;
	lexer->token = NULL;
	lexer->next = NULL;
	lexer->prev = NULL;
	return (lexer);
}


//check for special characters and create tokens:
// - pipes
// - redirections
// - heredoc
void	ft_tokenizer(t_lexer *lexer)
{
	if (!ft_strncmp(lexer->str, "|", 1) && ft_strlen(lexer->str) == 1)
		lexer->token = ft_strdup("PIPE");
	else if (!ft_strncmp(lexer->str, ">", 1) && ft_strlen(lexer->str) == 1)
		lexer->token = ft_strdup("REDIR_OUT");
	else if (!ft_strncmp(lexer->str, ">>", 2) && ft_strlen(lexer->str) == 2)
		lexer->token = ft_strdup("REDIR_APPEND");
	else if (!ft_strncmp(lexer->str, "<", 1) && ft_strlen(lexer->str) == 1)
		lexer->token = ft_strdup("REDIR_IN");
	else if (!ft_strncmp(lexer->str, "<<", 2) && ft_strlen(lexer->str) == 2)
		lexer->token = ft_strdup("HEREDOC");
	if (lexer->token)
	{
		free(lexer->str);
		lexer->str = NULL;
	}
}
