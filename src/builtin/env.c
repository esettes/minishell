/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:07:06 by iostancu          #+#    #+#             */
/*   Updated: 2024/02/29 23:30:40 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(t_pipe *data)
{
	int	i;
	int	envp_minish_size;

	i = 0;
	envp_minish_size = get_array_size(data->envp_minish);
	while (i < envp_minish_size)
	{
		printf("%s\n", data->envp_minish[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_envp_minishell(t_pipe *data, char *envp[])
{
	size_t	len;
	size_t	i;
	size_t	j;

	len = 0;
	while (envp[len])
		len++;
	data->envp_minish = malloc(sizeof(char *) * (len + 1));
	if (!data->envp_minish)
		return (EXIT_FAILURE);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (envp[i] && (f_strncmp(envp[i], "OLDPWD", 6) == 0))
			i++;
		data->envp_minish[j] = f_strdup(envp[i]);
		if (!data->envp_minish[j])
			return (EXIT_FAILURE);
		i++;
		j++;
	}
	data->envp_minish[j] = NULL;
	return (EXIT_SUCCESS);
}
