/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yacc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:44 by antosanc          #+#    #+#             */
/*   Updated: 2024/04/13 17:12:53 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Aqui la idea principal es añadir los comandos a la estructura t_cmd, para ello hay que contar argumentos
crear las estructuras suficientes para albergar todos los comandos y meterlos en t_scmd cada comando simple, 
en este punto hay que controlar heredoc. En teoria, si heredoc usa variables de entorno $HOME dentro de el
hay que expandirlas*/

#include "../../inc/headers/minishell.h"

// Falta añadirle la comprobacion de redirecciones y el heredoc que no se como hacerlo aun
static int	fill_scmd(t_scmd *scmd, t_list *tokens)
{
	int	t_len;

	while (scmd->argc < scmd->n_available_args)
	{
		t_len = ft_strlen((char *)tokens->content);
		scmd->args[scmd->argc] = (char *)malloc(sizeof(char) * t_len + 1);
		if (!scmd->args[scmd->argc])
			return (EXIT_FAILURE);
		scmd->args[scmd->argc] = ft_strdup((char *)tokens->content);
		tokens = tokens->next;
		scmd->argc++;
	}
	return (EXIT_SUCCESS);
}

static int	create_scmd(t_scmd **scmd, t_list *tokens)
{
	int	i;

	i = 0;
	while (scmd[i])
	{
		scmd[i]->n_available_args = count_scmd_args(tokens);
		scmd[i]->args = malloc(sizeof(char *) * scmd[i]->n_available_args + 1);
		if (!scmd[i]->args)
			return (EXIT_FAILURE);
		scmd[i]->argc = 0;
		scmd[i]->append = 0;
		scmd[i]->in_f = NULL;
		scmd[i]->out_f = NULL;
		if (fill_scmd(scmd[i], tokens))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

t_cmd	*yacc_tony(t_cmd *cmd, t_list *tokens)
{
	int	i;

	cmd->n_available_scmd = count_cmd(tokens);
	cmd->n_scmd = 0;
	cmd->scmd = ft_calloc(cmd->n_available_scmd + 1, sizeof(t_scmd *));
	if (!cmd->scmd)
		return (NULL);
	i = -1;
	while (++i < cmd->n_available_scmd)
	{
		cmd->scmd[i] = (t_scmd *)malloc(sizeof(t_scmd));
		if (!cmd->scmd[i])
		{
			while (--i > 0)
				free(cmd->scmd[i]);
			free(cmd->scmd);
			return (NULL);
		}
	}
	cmd->scmd[cmd->n_available_scmd] = NULL;
	if (create_scmd(cmd->scmd, tokens))
		free_cmd_tony(cmd);
	return (cmd);
}