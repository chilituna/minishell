/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:13:16 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/28 10:51:31 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf(BLUE2 "COMMAND: %d\n" RESET, cmd->index + 1);

	while (cmd->tokens[i])
	{
		printf("%s\n", cmd->tokens[i]);
		i++;
	}
}

// READ
// EVALUATE
// PRINT
// LOOP
// show prompt
// read input from user (readline)
// add input to history (add_history)
// check for unclosed quotes
// split input into an array of strings
// lexer to create a linked list of the input and check for tokens
// parser to create a tree of the input and check for syntax errors
// execute the commands
// free memory
int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = NULL;
	if (argc != 1 || argv[1])
		ft_error_and_exit("usage: ./minishell", data);
	data = ft_malloc(sizeof(t_data), data);
	if (!data)
		ft_error_and_exit("malloc error", data);
	ft_print_banner();
	while (1)
	{
		data->prompt = readline(YELLOW ">>> " RESET);
		if (!data->prompt)
			ft_error_and_exit("readline error", data);
		if (data->prompt[0] != '\0')
			add_history(data->prompt);
		if (ft_check_quotes(data->prompt))
		{
			printf(GREEN "Quotes checked\n" RESET);
			data->lexer = ft_lexer(data->prompt, data);
			printf(GREEN "Lexer done\n" RESET);
			data->cmd = ft_parser(data->lexer, data);
			printf(GREEN "Commands grouped\n"RESET);
			//print cmds:
			while (data->cmd)
			{
				ft_print_cmd(data->cmd);
				data->cmd =
				data->cmd->next;
			}
			ft_check_cmds(data->cmd);
			// ft_execute();
			(void)envp;
		}
		ft_free_data(data);
	}
	return (0);

}

//print minishell banner when strting the program

void	ft_print_banner_2(void)
{
	printf(BLUE3"             *               ***   ***\n");
	printf("           **                 ***   ***\n");
	printf("           **                  **    **\n");
	printf("           **                  **    **\n");
	printf("   ****    **                  **    **\n");
	printf("  * **** * **  ***      ***    **    **\n");
	printf(" **  ****  ** * ***    * ***   **    **\n");
	printf("****       ***   ***  *   ***  **    **\n");
	printf("  ***      **     ** **    *** **    **\n");
	printf("    ***    **     ** ********  **    **\n");
	printf("      ***  **     ** *******   **    **\n");
	printf(" ****  **  **     ** **        **    **\n");
	printf("* **** *   **     ** ****    * **    **\n");
	printf("   ****    **     **  *******  *** * *** *\n");
	printf("            **    **   *****    ***   ***\n");
	printf("                 *\n");
	printf("                 *\n");
	printf("                * " RESET);
	printf(BLUE1 "     by Alise & Luis\n" RESET);
	printf(BLUE3"               *\n\n" RESET);
}

void	ft_print_banner_1(void)
{
	printf(BLUE1 "\n    ._____.___ .___ .______  .___\n");
	printf("    :         |: __|:      \\ : __|\n");
	printf("    |   \\  /  || : ||       || : |\n");
	printf("    |   |\\/   ||   ||   |   ||   |\n");
	printf("    |___| |   ||   ||___|   ||   |\n");
	printf("          |___||___|    |___||___|\n\n" RESET);
}

void	ft_print_banner(void)
{
	ft_print_banner_1();
	ft_print_banner_2();
}
