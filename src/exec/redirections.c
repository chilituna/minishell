/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:34:50 by lperez-h          #+#    #+#             */
/*   Updated: 2024/04/17 16:13:35 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_redirs(t_redir *last_i, t_redir *last_o, t_cmd *cmds)
{
	if (last_i)
	{
		if (ft_redirect_input(last_i, cmds) == 1)
			return (1);
	}
	if (last_o)
	{
		if (ft_redirect_output(last_o, cmds) == 1)
			return (1);
	}
	return (0);
}

//Function to check pipeline redirections
//it will iterate the command list and the
//redirection list. For each command it will
//iterate the corresponding redir list
//for input the last redir struct will be checked
//for output all redir structs will be checked
int	ft_handle_redirs(t_cmd *cmds)
{
	t_redir	*tmp_redir;
	t_redir	*last_i;
	t_redir	*last_o;

	last_i = NULL;
	last_o = NULL;
	tmp_redir = cmds->redir;
	while (tmp_redir)
	{
		if (tmp_redir->in)
		{
			if (ft_check_infile(tmp_redir, cmds) == 1)
				return (1);
			last_i = tmp_redir;
		}
		if (tmp_redir->out)
		{
			if (ft_check_outfile(tmp_redir, cmds) == 1)
				return (1);
			last_o = tmp_redir;
		}
		tmp_redir = tmp_redir->next;
	}
	return (ft_open_redirs(last_i, last_o, cmds));
}
