/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yacc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:19:47 by antosanc          #+#    #+#             */
/*   Updated: 2024/05/02 12:00:39 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

int	count_cmd(t_token_lst *token_lst)
{
	int	len;

	len = 1;
	while (token_lst)
	{
		if (((char *)token_lst->content)[0] == '|' && token_lst->quotes == 0)
			len++;
		token_lst = token_lst->next;
	}
	return (len);
}

int	count_scmd_args(t_token_lst *token_lst)
{
	int			len;
	char		*content;
	int			flag;

	len = 0;
	flag = 0;
	while (token_lst && ((char *)token_lst->content)[0] != '|')
	{
		content = token_lst->content;
		if (flag == 1)
			flag = 0;
		else if (ft_strncmp(content, "<<", 2) == 0)
			flag = 1;
		else if (content[0] == '<' || content[0] == '>'
			&& token_lst->quotes == 0)
			flag = 1;
		else
			len++;
		token_lst = token_lst->next;
	}
	if (len == 0)
		len++;
	return (len);
}

void	free_scmd_tony(t_cmd *cmd)
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

void	free_cmd_tony(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->scmd)
		free_scmd_tony(cmd);
	free(cmd);
	cmd = NULL;
}
