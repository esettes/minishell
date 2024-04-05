/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:27:39 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/05 20:26:05 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t		var_lenght(char *var);
static int	check_chars(char *var, char *cmd);
static void	free_vars(char *s1, char *s2, char *s3);

int	is_correct_env_variable(char *var, char *cmd)
{
	size_t	count;
	int		ret;
	int		i;

	count = 0;
	ret = check_chars(var, cmd);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (ft_isdigit(var[i]) || var[i] == '_')
			count++;
		i++;
	}
	if (count == var_lenght(var))
		ret = FALSE;
	if (ret == FALSE)
	{
		print_cmd_error(var, cmd);
		g_signal = 1;
		return (FALSE);
	}
	return (TRUE);
}

static int check_chars(char *var, char *cmd)
{
	int		i;
	size_t	ret;

	i = 0;
	ret = TRUE;
	if (!(ft_isalpha(var[0]) || var[0] == '_'))
		ret = FALSE;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			ret = FALSE;
		i++;
	}
	if (var[f_strlen(var) - 1] == '='
		&& f_strncmp(cmd, "unset", f_strlen(cmd)) == 0)
		ret = FALSE;
	return (ret);
}

int	change_var_value(char **envp_minish, char *raw_variable)
{
	int		i;
	char	*in_var;
	char	*var;
	int		envp_size;

	i = 0;
	in_var = get_env_variable(raw_variable);
	envp_size = get_array_size(envp_minish);
	if (!in_var)
		return (EXIT_SUCCESS);
	while (i < envp_size)
	{
		var = get_env_variable(envp_minish[i]);
		if (f_strict_strncmp(var, in_var, f_strlen(in_var)) == 0)
		{
			free(envp_minish[i]);
			envp_minish[i] = f_strdup(raw_variable);
			free_vars(in_var, var, raw_variable);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	free_vars(in_var, var, raw_variable);
	return (EXIT_SUCCESS);
}

static void	free_vars(char *s1, char *s2, char *s3)
{
	free(s1);
	free(s2);
	free(s3);
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

size_t	var_lenght(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}
