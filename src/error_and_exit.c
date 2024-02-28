/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:56:57 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/28 16:48:33 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if readline is NULL, there was error with readline function
// or the user typed Ctrl+D to signal end-of-file (EOF).
// if readline history exists, it is freed.
void	ft_error_and_exit(char *str, t_data *data)
{
	if (isatty(STDIN_FILENO))
		printf(RED "ERROR: %s\n" RESET, str);
	if (history_length > 0)
		rl_clear_history();
	if (data)
		ft_free_data(data);
	if (data->env)
		ft_free_env(data->env);
	free(data);
	exit(1);
}
