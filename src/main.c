/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:13:16 by aarponen          #+#    #+#             */
/*   Updated: 2024/03/12 15:26:05 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf(BLUE1 "COMMAND: %d\n" RESET, cmd->index + 1);
	while (cmd->cmd_arg[i])
	{
		printf("%s\n", cmd->cmd_arg[i]);
		i++;
	}
	if (cmd->in)
		printf(BLUE3 "IN: %s\n" RESET, cmd->in);
	if (cmd->out)
		printf(BLUE3 "OUT: %s\n" RESET, cmd->out);
}

//store environment variables in data
void	ft_init_data(char **envp, t_data *data)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	data->env = ft_malloc((i + 1) * sizeof(char *), data);
	i = 0;
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i], data);
		i++;
	}
	data->lexer = NULL;
	data->cmd = NULL;
	data->prompt = NULL;
	data->exit_status = 0;
	ft_print_banner();
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
		ft_error_minishell("usage: ./minishell");
	data = malloc(sizeof(t_data));
	if (!data)
		ft_error_and_exit("malloc error", data);
	ft_init_data(envp, data);
	while (1)
	{
		ft_signals_interactive();
		data->prompt = readline(YELLOW "minishell $ " RESET);
		if (!data->prompt)
			ft_error_and_exit("readline error", data);
		ft_signals_running();
		if (data->prompt[0] != '\0')
			add_history(data->prompt);
		if (ft_check_quotes(data->prompt))
		{

			// printf(GREEN "...Quotes checked...\n" RESET);
			data->lexer = ft_lexer(data->prompt, data);
			// printf(GREEN "...Lexer done...\n" RESET);
			data->cmd = ft_parser(data->lexer, data);
			// printf(GREEN "...Commands grouped...\n"RESET);
			if (!ft_check_cmds(data->cmd))
				continue ;
			// printf(GREEN "...Ready to execute...\n" RESET);
			// printf("OUTCOME:\n");
			ft_execute_cmds(data->cmd);
			// printf(GREEN "...Commands executed...\n" RESET);
		}
		ft_free_data(data);
		// printf(GREEN "...Memory freed...\n" RESET);
	}
	free(data);
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
