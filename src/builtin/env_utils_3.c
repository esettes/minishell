/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:07:23 by iostancu          #+#    #+#             */
/*   Updated: 2024/07/08 16:44:40 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_env_var_value(char **envp_minish, char *var)
{
	size_t	i;
	char	*env_var;

	i = 0;
	if (!envp_minish || !*envp_minish)
		return (NULL);
	while (envp_minish[i])
	{
		env_var = get_env_variable(envp_minish[i]);
		if (!env_var)
			return (NULL);
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
		free(env_var);
		i++;
	}
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

void	print_env_not_set(char *cmd, char *var)
{
	ft_putstrc_fd(RED_, "minishell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstrc_fd(RED_, cmd, STDERR_FILENO);
		ft_putstrc_fd(RED_, ": ", STDERR_FILENO);
	}
	if (var)
	{
		ft_putstrc_fd(RED_, var, STDERR_FILENO);
		ft_putstrc_fd(RED_, ": ", STDERR_FILENO);
	}
	ft_putstrc_fd(RED_, "not set\n", STDERR_FILENO);
}

void	print_err_msg(char *cmd, char *var, char *msg)
{
	ft_putstrc_fd(RED_, "minishell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstrc_fd(RED_, cmd, STDERR_FILENO);
		ft_putstrc_fd(RED_, ": ", STDERR_FILENO);
	}
	if (var)
	{
		ft_putstrc_fd(RED_, var, STDERR_FILENO);
		ft_putstrc_fd(RED_, ": ", STDERR_FILENO);
	}
	if (msg)
	{
		ft_putstrc_fd(RED_, msg, STDERR_FILENO);
		ft_putstrc_fd(RED_, "\n", STDERR_FILENO);
	}
}
