/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:07 by antosanc          #+#    #+#             */
/*   Updated: 2024/04/25 21:59:51 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

//Borrar cuando termine de probar

/*void print_cmd_arguments(const t_cmd *cmd) {
    if (cmd == NULL) {
        printf("No command data available.\n");
        return;
    }

    printf("Total subcommands: %d\n", cmd->n_scmd);
    for (int i = 0; i < cmd->n_scmd; i++) {
        t_scmd *scmd = cmd->scmd[i];
        if (scmd == NULL) {
            printf("Subcommand %d is null.\n", i + 1);
            continue;
        }

        printf("Subcommand %d:\n", i + 1);
        printf("  Number of arguments argc: %d\n", scmd->argc);
        for (int j = 0; j < scmd->argc; j++) {
            printf("    Arg %d: %s\n", j + 1, scmd->args[j]);
        }

        // Optionally print redirection info
        if (scmd->in_f) {
            printf("  Input redirected from: %s\n", scmd->in_f);
        }
        if (scmd->out_f) {
            printf("  Output redirected to: %s", scmd->out_f);
            if (scmd->append) {
                printf(" (append mode)");
            }
            printf("\n");
        }
    }
}*/

static int	parse_checker(t_cmd *cmd, char *str, char **envp)
{
	t_token		*token;
	t_token_lst	*head;

	token = lex_tony(str, envp);
	if (token == NULL)
		return (EXIT_FAILURE);
	if (validator_tony(token))
		return (clear_all(&token, NULL), EXIT_FAILURE);
	head = token->token_lst;
	cmd = yacc_tony(cmd, &token->token_lst);
	token->token_lst = head;
	if (cmd == NULL)
		return (clear_all(&token, NULL), EXIT_FAILURE);
	return (clear_all(&token, NULL), EXIT_SUCCESS);
}

t_cmd	*parser(char *str, char **envp)
{
	t_cmd	*command;

	if (!str || !*str || !envp || !*envp)
		return (NULL);
	command = ft_calloc(1, sizeof(t_cmd));
	if (!command)
		return (NULL);
	if (parse_checker(command, str, envp))
	{
		g_signal = 2;
		return (free(command), NULL);
	}
	return (command);
}

//Borrar cuando termine de probar
/*int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*str = "< Makefile cat";
	parser(str, envp);
}*/