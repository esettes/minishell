/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:41:36 by iostancu          #+#    #+#             */
/*   Updated: 2024/05/11 15:50:25 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_new_envp_minish(char ***envp_minish, char **tmp);

size_t	get_array_size(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

/**
 * @brief Returns the variable clear, without '=', from string like 'var=value'
 * 
 * @param var 
 * @return char* 
 */
char	*get_env_variable(char *var)
{
	size_t	i;
	char	*aux;

	i = 0;
	if (!var)
		return (NULL);
	while (var[i] && var[i] != '=')
		i++;
	aux = malloc(sizeof(char) * (i + 1));
	if (!aux)
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		aux[i] = var[i];
		i++;
	}
	aux[i] = '\0';
	return (aux);
}

/**
 * @brief Get the env variable from the minishell environment
 * 
 * @param envp_minish 
 * @param var variable inserted in terminal
 * @return char* variable without '='
 */
char	*get_env_variable_from_minish_environ(char **envp_minish, char *var)
{
	size_t	i;
	char	*env_var;

	i = 0;
	while (envp_minish[i])
	{
		if (f_strncmp(envp_minish[i], var, f_strlen(var)) == 0)
		{
			env_var = get_env_variable(envp_minish[i]);
			if (f_strict_strncmp(env_var, var, f_strlen(env_var)) == 0)
				return (env_var);
		}
		i++;
	}
	return (NULL);
}

/**
 * @brief looks in envp_minish if the variable already exist
 * 
 * @param envp_minish 
 * @param raw_variable can recieve 'var=' or 'var=value', but no 'var'
 * @return int 
 */
int	env_var_already_exist(char **envp_minish, char *raw_variable)
{
	char	*var;
	char	*var_in_envp_minish;

	var = get_env_variable(raw_variable);
	if (!var)
		return (FALSE);
	var_in_envp_minish = get_env_variable_from_minish_environ(envp_minish, var);
	if (!var_in_envp_minish)
	{
		free(var);
		return (FALSE);
	}
	free(var);
	free(var_in_envp_minish);
	return (TRUE);
}

char	**create_new_var(t_pipe *data, char *var)
{
	size_t	len;
	char	**tmp;

	len = 0;
	len = get_array_size(data->envp_minish);
	tmp = malloc(sizeof(char *) * (len + 2));
	if (!tmp)
		return (NULL);
	len = 0;
	while (data->envp_minish[len])
	{
		tmp[len] = f_strdup(data->envp_minish[len]);
		len++;
	}
	tmp[len] = f_strdup(var);
	tmp[len + 1] = NULL;
	free_memory((const char **)data->envp_minish,
		get_array_size(data->envp_minish));
	return (tmp);
}

void	create_new_envp_minish(char ***envp_minish, char **tmp)
{
	size_t	i;

	i = 0;
	*envp_minish = malloc(sizeof(char *) * (get_array_size(tmp) + 1));
	if (!(*envp_minish))
		return ;
	while (tmp[i])
	{
		*envp_minish[i] = f_strdup(tmp[i]);
		printf("envp_minish[%zu]: %s\n", i, *envp_minish[i]);
		i++;
	}
	*envp_minish[i] = NULL;
	free_memory((const char **)tmp, get_array_size(tmp));
}
