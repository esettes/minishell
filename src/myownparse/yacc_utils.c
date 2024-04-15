/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yacc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:19:47 by antosanc          #+#    #+#             */
/*   Updated: 2024/04/15 22:42:28 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

//comprobar que este bien 
int	count_cmd(t_list *tokens)
{
	int	len;

	len = 1;
	while(tokens)
	{
		if (((char *)tokens->content)[0] == '|')
			len++;
		tokens = tokens->next;
	}
	return (len );
}

int	count_scmd_args(t_list *tokens)
{
	int	len;

	len = 0;
	while (tokens && ((char *)tokens->content)[0] != '|')
	{
		tokens = tokens->next;
		len++;
	}
	return (len);
}

void	free_cmd_tony(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	if (!cmd)
		return ;
	while (cmd->scmd[i])
	{
		j = 0;
		if (cmd->scmd[i]->args)
		{
			while (cmd->scmd[i]->args[j])
				free(cmd->scmd[i]->args[j++]);
			free(cmd->scmd[i]->args);
			cmd->scmd[i]->args = NULL;
		}
		free(cmd->scmd[i]->in_f);
		free(cmd->scmd[i]->out_f);
		free(cmd->scmd[i]);
		cmd->scmd[i] = NULL;
		i++;
	}
	free(cmd->scmd);
	cmd->scmd = NULL;
}
