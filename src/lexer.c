/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:25:16 by aarpo e           #+#    #+#             */
/*   Updated: 2024/02/24 17:28:38 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*ft_pick_string(char *str, int i, t_lexer *lexer)
{
	int		start;
	int		end;

	start = i;
	if (str[i] == '\'')
	{
		while (str[i] != '\'')
			i++;
		end = i;
	}
	else if (str[i] == '\"')
	{
		while (str[i] != '\"')
			i++;
		end = i;
	}
	else
	{
		while (str[i] != ' ' && str[i] != '\0')
			i++;
		end = i;
	}
	lexer->str = ft_copysub(str, start, end);
	return (lexer);
}

//split input into an array of strings
//create a linked list lexer that stores the words from the input
//send to function to check for special characters and create tokens
//return the linked list
t_lexer	*ft_lexer(char *str)
{
	int		i;
	t_lexer	*head;
	t_lexer	*tmp;
	t_lexer	*new;

	i = 0;
	while (str[i])
	{
		new = ft_init_lexer(new, i);
		ft_pick_string(str, i, new);
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
