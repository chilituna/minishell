/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarpo e  <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:04:52 by aarpo e           #+#    #+#             */
/*   Updated: 2024/03/17 12:09:34 by aarpo e          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Adds the node ’new’ at the end of the list.
void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*p;

	if (*lst == NULL)
		*lst = new;
	else
	{
		p = ft_lstlast(*lst);
		p->next = new;
	}
}

// Returns the last node of the list.
t_env	*ft_lstlast(t_env *lst)
{
	t_env	*p;

	if (lst == NULL)
		return (NULL);
	p = lst;
	while (p->next != NULL)
		p = p->next;
	return (p);
}

// Allocates (with malloc(3)) and returns a new node.
// The member variable ’content’ is initialized with
// the value of the parameter ’content’. The variable
// ’next’ is initialized to NULL
t_env	*ft_lstnew(char *content, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(*env));
	if (!env)
		return (NULL);
	env->var = content;
	env->value = value;

	env->next = NULL;
	return (env);
}


