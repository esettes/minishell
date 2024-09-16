/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:27:39 by iostancu          #+#    #+#             */
/*   Updated: 2024/09/16 16:20:30 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_var(t_list **env, char *rep_var, char *var_name)
{
	t_list	*line;

	line = *env;
	while (ft_strncmp(line->content, var_name, ft_strlen(var_name)))
		line = line->next;
	free(line->content);
	line->content = ft_strdup(rep_var);
	*rep_var = '?';
	free(var_name);
}

t_list	**exec_export(t_list **env, char **new_vars)
{
	int	i;

	if (!new_vars[1] || !check_syntax(env, &new_vars[1]))
		return (env);
	i = 0;
	while (new_vars[++i])
		if (new_vars[i][0] != '?')
			ft_lstadd_back(env, ft_lstnew(ft_strdup(new_vars[i])));
	return (env);
}

void	exec_env(t_list **env)
{
	t_list	*line;

	line = *env;
	while (line)
		(printf("%s\n", (char *) line->content), line = line->next);
}

t_list	**exec_unset(t_list **env, char **name)
{
	char	*full_name;
	t_list	*line;
	t_list	*tmp;

	if (!name[1])
		return (ft_printf("unset: not enough arguments\n"), env);
	full_name = ft_strjoin(name[1], "=");
	line = *env;
	while (line)
	{
		if (!ft_strncmp((char *)line->content, full_name, ft_strlen(full_name)))
		{
			ft_lstdelnode(env, line, tmp);
			if (!ft_lstsize(*env))
				*env = 0;
			break ;
		}
		tmp = line;
		line = line->next;
	}
	free(full_name);
	return (env);
}

char	*ft_getenv(t_list **env, char *name, char *value)
{
	char	*full_name;
	char	**split_name;
	t_list	*line;

	full_name = ft_strjoin(name, "=");
	line = *env;
	while (line)
	{
		if (!ft_strncmp((char *)line->content, full_name, ft_strlen(full_name)))
		{
			free(full_name);
			split_name = ft_split(line->content, '=');
			ft_strlcpy(value, split_name[1], BUF_SIZE);
			free_dp(split_name);
			return (value);
		}
		line = line->next;
	}
	free(full_name);
	return (0);
}
