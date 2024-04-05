/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:07:23 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/05 20:07:24 by iostancu         ###   ########.fr       */
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

char	*ft_getenv(char **envp, char *var_name)
{
	size_t	x;
	size_t	tam;

	x = ZERO;
	tam = ft_strlen(var_name);
	while (envp[x])
	{
		if (!ft_strncmp(var_name, envp[x], tam) && '=' == envp[x][tam])
			return (&envp[x][tam + TRUE]);
		++x;
	}
	return (NULL);
}


