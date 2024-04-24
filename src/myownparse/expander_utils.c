/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:59:01 by antosanc          #+#    #+#             */
/*   Updated: 2024/04/19 22:43:49 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

int	len_expanded_str(char *str, char *env_value)
{
	int	len_str;
	int	i;

	len_str = 0;
	while (str[len_str] != '$' && str[len_str])
		len_str++;
	i = len_str;
	while ((ft_isalnum(str[i]) || str[i] == '_') && str[i])
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
	tmp_envp = envp;
	while (tmp_envp[i])
	{
		if (ft_strncmp(var_env, tmp_envp[i], ft_strlen(var_env)) == 0
			&& tmp_envp[i][ft_strlen(var_env)] == '=')
		{
			j = 0;
			while (tmp_envp[i][j] != '=' && tmp_envp[i][j])
				j++;
			if (tmp_envp[i][j + 1])
			{
				free(var_env);
				return (ft_substr(tmp_envp[i] + j, 1,
						ft_strlen(tmp_envp[i]) - (j + 1)));
			}
		}
		i++;
	}
	return (ft_strdup(""));
}
