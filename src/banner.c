/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarpo e  <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:01:44 by aarpo e           #+#    #+#             */
/*   Updated: 2024/03/13 13:02:11 by aarpo e          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
