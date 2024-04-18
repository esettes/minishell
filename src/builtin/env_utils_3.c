/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:07:23 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/18 19:46:22 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_len(char **env)
{
	register size_t	x;

	x = ZERO;
	while (NULL != env[x])
		x++;
	return (x);
}

size_t	search_in_env(char **env, char *to_search)
{
	register size_t	x;
	register size_t	to_search_len;

	x = ZERO;
	to_search_len = ft_strlen(to_search);
	while (ft_strncmp(to_search, env[x], to_search_len))
		x++;
	return (x);
}

char	*get_env_var_value(char **envp_minish, char *var)
{
	size_t	i;
	char	*env_var;

	i = 0;
	while (envp_minish[i])
	{
		env_var = get_env_variable(envp_minish[i]);
		if (f_strict_strncmp(env_var, var, f_strlen(var)) == 0)
		{
			if (envp_minish[i][f_strlen(env_var)] == '\0')
			{
				free(env_var);
				return (NULL);
			}
			free(env_var);
			return (envp_minish[i] + f_strlen(var) + 1);
		}
		i++;
	}
	free(env_var);
	return (NULL);
}

void	init_env(char **env, size_t len, char **envp_minish)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		env[i] = f_strdup(envp_minish[i]);
		i++;
	}
}
