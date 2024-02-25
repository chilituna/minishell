/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:13:16 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/25 15:05:36 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_data(t_data *data)
{
	data->prompt = NULL;
	data->lexer = NULL;
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

	if (argc != 1 || argv[1])
		ft_error_and_exit("usage: ./minishell");
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		ft_error_and_exit("calloc error");
	ft_print_banner();
	while (1)
	{
		data->prompt = readline(">>> ");
		if (!data->prompt)
			ft_error_and_exit("readline error");
		if (data->prompt[0] != '\0')
			add_history(data->prompt);
		if (!ft_check_quotes(data->prompt))
		{
			data->lexer = ft_lexer(data->prompt);
			// ft_parser();
			// ft_execute();
			(void)envp;
			printf("Input as lexer:\n");
			while (data->lexer)
			{
				if (data->lexer->token)
					printf("%s\n", data->lexer->token);
				else
					printf("%s\n", data->lexer->str);
				data->lexer = data->lexer->next;
			}
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
