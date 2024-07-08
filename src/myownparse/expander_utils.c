/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:59:01 by antosanc          #+#    #+#             */
/*   Updated: 2024/07/08 16:45:59 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

int	len_expanded_str(char *str, char *env_value)
{
	int	len_str;
	int	i;

	len_str = 0;
	while (str[len_str] && str[len_str] != '$')
		len_str++;
	i = len_str;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	while (str[i])
	{
		i++;
		len_str++;
	}
	return (len_str + ft_strlen(env_value));
}

char	*get_env_value(char *var_env, char **envp)
{
	int		i;
	int		j;
	char	**tmp_envp;

	i = 0;
	if (!envp || !*envp)
		return (ft_strdup(""));
	tmp_envp = envp;
	while (tmp_envp[i])
	{
		if (ft_strncmp(var_env, tmp_envp[i], ft_strlen(var_env)) == 0
			&& tmp_envp[i][ft_strlen(var_env)] == '=')
		{
			j = 0;
			while (tmp_envp[i][j] && tmp_envp[i][j] != '=')
				j++;
			if (tmp_envp[i][j + 1])
				return (ft_substr(tmp_envp[i] + j, 1,
						ft_strlen(tmp_envp[i]) - (j + 1)));
		}
		i++;
	}
	return (ft_strdup(""));
}
