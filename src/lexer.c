/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarpo e  <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:25:16 by aarpo e           #+#    #+#             */
/*   Updated: 2024/02/21 19:06:44 by aarpo e          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//split input into an array of strings
//create a linked list lexer that stores the words from the input
//send to function to check for special characters and create tokens
//return the linked list
t_lexer	*ft_lexer(char **argv)
{
	int		i;
	t_lexer	*head;
	t_lexer	*tmp;
	t_lexer	*new;

	i = 0;
	while (argv[i])
	{
		ft_init_lexer(new, i);
		new->str = argv[i];
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
		return (head);
	}
}

void	ft_init_lexer(t_lexer *lexer, int i)
{
	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		exit(1); // malloc_error function to free memory and exit
	lexer->index = i;
	lexer->str = NULL;
	lexer->next = NULL;
	lexer->prev = NULL;
}


//check for special characters and create tokens
void	ft_tokenizer(t_lexer *lexer)
{

}