/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:41:36 by iostancu          #+#    #+#             */
/*   Updated: 2024/03/13 23:42:45 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_array_size(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

/**
 * @brief Returns the variable, without '=', from a string like 'var=value'
 * 
 * @param var 
 * @return char* 
 */
char	*get_env_variable(char *var)
{
	size_t	i;
	char	*aux;

	i = 0;
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
 * @param var_value 
 * @param var 
 * @return char* 
 */
char	*get_env_variable_from_minish_environ(char **envp_minish, char *var)
{
	size_t	i;
	char	*aux;
	char	*env_var;

	i = 0;
	while (envp_minish[i])
	{
		if (f_strncmp(envp_minish[i], var, f_strlen(var)) == 0)
		{
			env_var = get_env_variable(envp_minish[i]);
			if (f_strict_strncmp(env_var, var, f_strlen(env_var)) == 0)
			{
				aux = f_strdup(envp_minish[i] + f_strlen(var) + 1);
				free(env_var);
				return (aux);
			}
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
	size_t	i;
	char	*var;

	i = 0;
	var = get_env_variable(raw_variable);
	while (envp_minish[i])
	{
		if (f_strncmp(envp_minish[i], var, f_strlen(var)) == 0)
		{
			free(var);
			return (TRUE);
		}
		i++;
	}
	free(var);
	return (FALSE);
}

char	**create_new_var(char **envp_minish, char *var)
{
	size_t	len;
	char	**tmp;
	size_t	aux;
	
	len = 0;
	len = get_array_size(envp_minish);
	aux = len;
	tmp = malloc(sizeof(char *) * (len + 2));
	if (!tmp)
		return (NULL);
	len = 0;
	while (envp_minish[len])
	{
		tmp[len] = f_strdup(envp_minish[len]);
		len++;
	}
	tmp[len] = f_strdup(var);
	tmp[len + 1] = NULL;
	free_memory((const char **)envp_minish, aux);
	return (tmp);
}
