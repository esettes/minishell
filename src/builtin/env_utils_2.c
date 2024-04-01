/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:41:36 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/02 01:01:55 by iostancu         ###   ########.fr       */
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
	//char	*aux;
	char	*env_var;

	i = 0;
	while (envp_minish[i])
	{
		if (f_strncmp(envp_minish[i], var, f_strlen(var)) == 0)
		{
			env_var = get_env_variable(envp_minish[i]);
			if (f_strict_strncmp(env_var, var, f_strlen(env_var)) == 0)
			{
				printf("environ f env_var: %s\n", env_var);
				printf("environ f var: %s\n", var);
				//aux = f_strdup(envp_minish[i] + f_strlen(var) + 1);
				//printf("environ f aux: %s\n", aux);
				//free(env_var);
				return (env_var);
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
	char	*var;
	char	*var_in_envp_minish;

	var = get_env_variable(raw_variable);
	if (!var)
		return (FALSE);
	var_in_envp_minish = get_env_variable_from_minish_environ(envp_minish, var);
	printf("var: %s\n", var);
	printf("var_in_envp_minish: %s\n", var_in_envp_minish);
	if (!var_in_envp_minish)
	{
		free(var);
		return (FALSE);
	}
	free(var);
	free(var_in_envp_minish);
	return (TRUE);
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
