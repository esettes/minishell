/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:59:16 by antosanc          #+#    #+#             */
/*   Updated: 2024/09/16 16:18:35 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_str(t_list **head)
{
	t_list	*line;
	char	*full_line;
	char	*appended_line;

	line = *head;
	full_line = malloc(sizeof(char *));
	*full_line = 0;
	while (line)
	{
		appended_line = ft_strjoin(full_line, (char *)line->content);
		free(full_line);
		full_line = appended_line;
		line = line->next;
	}
	ft_lstclear(head, (*free));
	free(head);
	return (full_line);
}

void	expand_vars(char *line, t_pipe *data, t_list **head, int *i)
{
	char	value[BUF_SIZE];
	char	*name;

	ft_lstadd_back(head, ft_lstnew(ft_substr(line, i[1], i[0] - i[1])));
	i[1] = i[0]++;
	if (line[i[0]] == '?')
		(ft_lstadd_back(head, ft_lstnew(ft_itoa(WEXITSTATUS(data->status)))),
			i[0]++);
	else if (line[i[0]] == -7 || !line[i[0]])
		ft_lstadd_back(head, ft_lstnew(ft_strdup("$")));
	else
	{
		while ((ft_isalnum(line[i[0]]) || line[i[0]] == '_') && line[i[0]])
			i[0]++;
		name = ft_substr(line, i[1] + 1, i[0] - i[1] - 1);
		if (ft_getenv(data->env, name, value))
			ft_lstadd_back(head, ft_lstnew(ft_strdup(value)));
		free(name);
	}
	i[1] = i[0];
}

char	*check_vars(t_pipe *data, char *line)
{
	t_list	**head;
	int		i[2];

	i[0] = -1;
	i[1] = 0;
	head = malloc(sizeof(t_list **));
	*head = 0;
	while (line[++i[0]])
	{
		while (line[i[0]] == DOLLAR)
			expand_vars(line, data, head, i);
		if (!line[i[0]])
			break ;
	}
	ft_lstadd_back(head, ft_lstnew(ft_substr(line, i[1], i[0] - i[1])));
	return (free(line), append_str(head));
}

char	**expand_metachar(t_pipe *data, char **rev_cmd)
{
	int	i;

	i = -1;
	while (rev_cmd[++i])
	{
		rev_cmd[i] = check_vars(data, rev_cmd[i]);
		rev_cmd[i] = reset_vars(rev_cmd[i]);
	}
	return (rev_cmd);
}
