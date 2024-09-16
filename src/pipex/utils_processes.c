/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:39 by iostancu          #+#    #+#             */
/*   Updated: 2024/09/16 18:55:16 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	f_perror(int code, char *name)
{
	if (code == -1)
		perror(name);
	return (code);
}

void	ft_lstdelnode(t_list **head, t_list *node, t_list *tmp)
{
	if (node == *head)
		*head = node->next;
	else
		tmp->next = node->next;
	free(node->content);
	free(node);
	if (!*head)
		free(head);
}

void	print_err_msg(char c)
{
	if (c == LESS_THAN || c == MORE_THAN || c == PIPE
		|| c == SIMPLE_QUOTE || c == DOUBLE_QUOTE)
		ft_printf("minishell: syntax error near unexpected token `%c'\n", c);
	else if (c == HERE_DOC)
		ft_printf("minishell: syntax error near unexpected token `heredoc'\n");
	else if (c == APPEND)
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
}

void	wait_cmds(t_pipe *data)
{
	int	i;

	i = -1;
	while (++i < data->n_cmd)
		process_waiting(data);
}

t_list	**run_export(t_list **env, char **cmd, t_pipe **d)
{
	if (!cmd[0])
	{
		exec_export_no_args(d);
		return (env);
	}
	return (exec_export((*d)->env, cmd));
}
