/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:13:16 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/18 17:25:17 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// READ
// EVALUATE
// PRINT
// LOOP
int	main(void)
{
	char	*prompt;
	//int		argc;
	//char	**argv;

	ft_print_banner();
	while (1)
	{
		// read input from user
		prompt = readline(">>> ");
		if (prompt == NULL)
			break ;
		// add input to history
		if (prompt[0] != '\0')
			add_history(prompt);
		// parse and tokenize input
		// execute command
		printf("You typed %s\n", prompt);
		// free memory
		free (prompt);
	}
	return (0);

}

//print minishell banner when strting the program

void	ft_print_banner(void)
{
	printf("\n    ._____.___ .___ .______  .___\n");
	printf("    :         |: __|:      \\ : __|\n");
	printf("    |   \\  /  || : ||       || : |\n");
	printf("    |   |\\/   ||   ||   |   ||   |\n");
	printf("    |___| |   ||   ||___|   ||   |\n");
	printf("          |___||___|    |___||___|\n\n");
	printf("             *               ***   ***\n");
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
	printf("                *        by Alise & Luis\n");
	printf("               *\n\n");
}
