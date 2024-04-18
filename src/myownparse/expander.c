/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:59:16 by antosanc          #+#    #+#             */
/*   Updated: 2024/04/17 23:27:56 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

static int	len_expanded_str(char *str, char *env_value)
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

static char	*fill_array(char *str, char *env_value, char *array)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 0;
	x = 0;
	while (str[i] != '$' && str[i])
		array[j++] = str[i++];
	i++;
	while ((str[i] == '?' || ft_isalnum(str[i]) || str[i] == '_') && str[i])
		i++;
	while (env_value && env_value[x])
		array[j++] = env_value[x++];
	while (str[i])
		array[j++] = str[i++];
	array[j] = '\0';
	return (array);
}
//Leak si la variable no esta definida
static char	*create_expanded_str(char *str, char *env_value, t_token *token)
{
	char	*array;
	int		len;

	len = len_expanded_str(str, env_value);
	array = (char *)malloc(len + 1);
	if (!array)
	{
		free(str);
		free(env_value);
		return (clear_all(token, "malloc has failed"));
	}
	return (fill_array(str, env_value, array));
}

static char	*get_env_value(char *var_env, char **envp)
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

char	*expander_process(char *str, t_token *token)
{
	char	*expanded_str;
	char	*env;
	int		l;
	int		i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] && !(str[i + 1] == '?'))
	{
		if (!((ft_isalnum(str[i + 1]) || str[i + 1] == '_') && str[i + 1]))
			return (str);
		l = 1;
		while ((ft_isalnum(str[i + l]) || str[i + l] == '_') && str[i + l])
			l++;
		env = ft_substr(str + i, 1, l - 1);
		env = get_env_value(env, token->envp);
		expanded_str = create_expanded_str(str, env, token);
		free(env);
	}
	else
		expanded_str = create_expanded_str(str, ft_itoa(g_signal), token);
	free(str);
	return (expanded_str);
}
