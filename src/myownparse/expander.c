/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:59:16 by antosanc          #+#    #+#             */
/*   Updated: 2024/09/04 18:17:29 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

static char	*fill_array(char *str, char *env_value, char *array)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 0;
	x = 0;
	while (str[i] && str[i] != '$')
		array[j++] = str[i++];
	i++;
	while (str[i] && (str[i] == '?' || ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	while (env_value && env_value[x])
		array[j++] = env_value[x++];
	while (str[i])
		array[j++] = str[i++];
	array[j] = '\0';
	return (array);
}

static char	*create_expanded_str(char *str, char *env_value, t_token **token)
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

static char	*expander_process(char *str, char **envp, t_token **token, int *i)
{
	char	*expanded_str;
	char	*env_key;
	char	*env_value;
	int		l;

	if (str[*i + 1] && !((ft_isalnum(str[*i + 1]) || str[*i + 1] == '_')))
		return (str);
	l = 1;
	while (str[*i + l] && (ft_isalnum(str[*i + l]) || str[*i + l] == '_'))
		l++;
	env_key = ft_substr(str + *i, 1, l - 1);
	env_value = get_env_value(env_key, envp);
	free(env_key);
	expanded_str = create_expanded_str(str, env_value, token);
	free(env_value);
	return (expanded_str);
}

char	*expander(char *str, char **envp, t_token **token)
{
	char	*expanded_str;
	int		i;
	char	*signal;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] && !(str[i + 1] == '?'))
		expanded_str = expander_process(str, envp, token, &i);
	else
	{
		signal = ft_itoa(exit_s);
		if (str[i + 1] != '\0')
			ft_strlcat(signal, str + 2, sizeof(str) - 1);
		expanded_str = create_expanded_str(str, signal, token);
		free(signal);
	}
	free(str);
	return (expanded_str);
}
