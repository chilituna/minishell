/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:47:15 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/10 08:47:23 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//remove quotes from the input:
//iterate through each argument:
//if quotes are found, removed them and replace with new string
void	ft_update_quotes(char **arg, int *j, char quote, t_cmd *cmd)
{
	int		start;

	start = *j;
	(*j)++;
	while ((*arg)[*j] && (*arg)[*j] != quote)
		(*j)++;
	if ((*arg)[*j] == quote)
	{
		*arg = ft_update_str(*arg, start, *j, cmd->data);
	}
}

void	ft_process_quotes(char **arg, t_cmd *cmd)
{
	int		j;
	char	quote;
	int		in_quote;

	j = 0;
	in_quote = 0;
	while ((*arg)[j])
	{
		if (((*arg)[j] == '\'' || (*arg)[j] == '\"') && !in_quote)
		{
			quote = (*arg)[j];
			in_quote = 1;
			ft_update_quotes(arg, &j, quote, cmd);
			in_quote = 0;
		}
		else if ((*arg)[j] == quote && in_quote)
			in_quote = 0;
		j++;
	}
}

void	ft_remove_quotes(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->cmd_arg[i])
	{
		ft_process_quotes(&cmd->cmd_arg[i], cmd);
		i++;
	}
}

char	*ft_update_str(char	*arg, int start, int len, t_data *data)
{
	char	*new_arg;

	new_arg = ft_strjoin(ft_substr(arg, 0, start, data),
			ft_substr(arg, start + 1, len - start - 1, data), data);
	free(arg);
	return (new_arg);
}

