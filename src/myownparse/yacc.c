/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yacc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:44 by antosanc          #+#    #+#             */
/*   Updated: 2024/04/17 22:42:30 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

static void	check_args(t_scmd *scmd, t_token_lst **token_lst)
{
	char	*direction;
	
	direction = (*token_lst)->content;
	*token_lst = (*token_lst)->next;
	if (direction[0] == '<')
	{
		if (scmd->in_f)
			free(scmd->in_f);
		scmd->in_f = ft_strdup((*token_lst)->content);
	}
	else
	{
		if (ft_strncmp(direction, ">>", 2) == 0)
			scmd->append = 1;
		if (scmd->out_f)
			free(scmd->out_f);
		scmd->out_f = ft_strdup((*token_lst)->content);
	}
}

static int	fill_scmd(t_scmd *scmd, t_token_lst **token_lst)
{
	if (ft_strncmp((*token_lst)->content, "<<", 2) == 0
			&& (*token_lst)->quotes == 0)
	{
		if (heredoc_init(scmd, token_lst))
			return (EXIT_FAILURE);
	}
	else if (((*token_lst)->content[0] == '<' || (*token_lst)->content[0] == '>')
		&& (*token_lst)->quotes == 0)
		check_args(scmd, token_lst);
	else
	{
		scmd->args[scmd->argc] = ft_strdup((*token_lst)->content);
		scmd->argc++;
	}
	*token_lst = (*token_lst)->next;
	return (EXIT_SUCCESS);
}

static int	create_scmd(t_scmd **scmd, t_token_lst **token_lst)
{
	int	i;

	i = 0;
	while (scmd[i] && *token_lst)
	{
		scmd[i]->n_available_args = count_scmd_args(*token_lst);
		scmd[i]->args = malloc(sizeof(char *) * scmd[i]->n_available_args + 1);
		if (!scmd[i]->args)
			return (EXIT_FAILURE);
		scmd[i]->argc = 0;
		scmd[i]->append = 0;
		scmd[i]->in_f = NULL;
		scmd[i]->out_f = NULL;
		while (*token_lst && (*token_lst)->content[0] != '|')
		{
			if (fill_scmd(scmd[i], token_lst))
				return (EXIT_FAILURE);
		}
		if (*token_lst && (*token_lst)->content[0] == '|')
			*token_lst = (*token_lst)->next;
		i++;
	}
	return (EXIT_SUCCESS);
}

t_cmd	*yacc_tony(t_cmd *cmd, t_token_lst **token_lst)
{
	int	i;

	cmd->n_available_scmd = count_cmd(*token_lst);
	cmd->n_scmd = 0;
	cmd->scmd = ft_calloc(cmd->n_available_scmd + 1, sizeof(t_scmd *));
	if (!cmd->scmd)
		return (NULL);
	i = 0;
	while (i < cmd->n_available_scmd)
	{
		cmd->scmd[i] = (t_scmd *)malloc(sizeof(t_scmd));
		if (!cmd->scmd[i])
		{
			while (--i > 0)
				free(cmd->scmd[i]);
			free(cmd->scmd);
			return (NULL);
		}
		i++;
	}
	cmd->scmd[cmd->n_available_scmd] = NULL;
	if (create_scmd(cmd->scmd, token_lst))
		free_cmd_tony(cmd);
	return (cmd);
}