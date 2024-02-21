/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarpo e  <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:46:01 by aarpo e           #+#    #+#             */
/*   Updated: 2024/02/21 19:52:30 by aarpo e          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// group nodes together based on tokens
// each group becomes command

// first loop through lexer until a pipe is found
// take all nodes before pipe and group them together in a cmd node
// if no (further) pipes are found, take all nodes until the end of the list
// for each command, check for redirections
// create a redirection node for each (token and filename or delimeter if heredoc)
// 
