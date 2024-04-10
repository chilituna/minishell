/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:47:15 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/10 23:11:00 by aarponen         ###   ########.fr       */
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
		(*j)--;
	}
}

//remove quotes in case the file name has quotes:
//iterate through the string until a quote is found
//remove all the quotes of the same type
void	ft_process_redir_quotes(char **str, t_cmd *cmd)
{
	int		j;
	char	quote;
	char	*beginnig;
	char	*end;

	j = 0;
	quote = '\0';
	while ((*str)[j])
	{
		if ((*str)[j] == '\'' || (*str)[j] == '\"')
		{
			quote = (*str)[j];
			while ((*str)[j])
			{
				if ((*str)[j] == quote)
				{
					beginnig = ft_substr((*str), 0, j, cmd->data);
					end = ft_substr((*str), j + 1, ft_strlen(*str) - j - 1, cmd->data);
					free(*str);
					*str = ft_strjoin(beginnig, end, cmd->data);
					free(beginnig);
					free(end);
					j = 0;
				}
				j++;
			}
		}
		j++;
	}
}

//remove quotes from the command arguments
//iterate through the string until a quote is found
//update the string by removing the quotes of the same type
void	ft_process_quotes(char **arg, t_cmd *cmd)
{
	int		j;
	char	quote;
	int		in_quote;

	j = 0;
	quote = '\0';
	in_quote = 0;
	while ((*arg)[j])
	{
		if (((*arg)[j] == '\'' || (*arg)[j] == '\"') && !in_quote)
		{
			quote = (*arg)[j];
			in_quote = 1;
			ft_update_quotes(arg, &j, quote, cmd);
			in_quote = 0;
			if (j >= (int)ft_strlen(*arg))
				break ;
			j = 0;
		}
		else if ((*arg)[j] == quote && in_quote)
			in_quote = 0;
		j++;
	}
}

//remove quotes from the command arguments and redirections
void	ft_remove_quotes(t_cmd *cmd)
{
	int		i;
	t_redir	*tmp;

	i = 0;
	while (cmd->cmd_arg[i])
	{
		ft_process_quotes(&cmd->cmd_arg[i], cmd);
		i++;
	}
	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->in)
			ft_process_redir_quotes(&tmp->in, cmd);
		if (tmp->out)
			ft_process_redir_quotes(&tmp->out, cmd);
		tmp = tmp->next;
	}
}

//update the string by removing the quotes
//return the new string
char	*ft_update_str(char	*arg, int start, int len, t_data *data)
{
	char	*new_arg;
	char	*str1;
	char	*str2;
	char	*str3;

	str1 = ft_substr(arg, 0, start, data);
	str2 = ft_substr(arg, start + 1, len - start - 1, data);
	str3 = ft_substr(arg, len + 1, ft_strlen(arg) - len - 1, data);
	new_arg = ft_strjoin(str1, str2, data);
	free(str1);
	free(str2);
	str1 = ft_strdup(new_arg, data);
	free(new_arg);
	new_arg = ft_strjoin(str1, str3, data);
	free(str1);
	free(str3);
	free(arg);
	return (new_arg);
}
