/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:46:01 by aarpo e           #+#    #+#             */
/*   Updated: 2024/02/24 16:56:05 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// put quotes together
// ft_organize_quotes(t_lexer *lexer)
// {
//     t_lexer *tmp;
//     t_lexer *new;
//     t_lexer *head;

//     tmp = lexer;
//     while (tmp)
//     {
//         if (tmp->token == "DQUOTE" || tmp->token == "SQUOTE")
//         {
//             new = ft_init_lexer(new, tmp->index);
//             new->str = tmp->str;
//             new->token = tmp->token;
//             if (tmp->index == 0)
//                 head = new;
//             else
//             {
//                 head->next = new;
//                 new->prev = head;
//             }
//             head = new;
//             tmp = tmp->next;
//         }
//         else
//             tmp = tmp->next;
//     }
//     return (head);
// }


// group nodes together based on tokens
// each group becomes command

// first loop through lexer until a pipe is found
// take all nodes before pipe and group them together in a cmd node
// if no (further) pipes are found, take all nodes until the end of the list
// for each command, check for redirections
// create a redirection node for each (token and filename or delimeter if heredoc)
// remove the redirection nodes from lexer
// check if first command is a builtin and store a function pointer to the corresponding function
// combine remaining words into **char for execve

