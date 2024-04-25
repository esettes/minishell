/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:59:16 by antosanc          #+#    #+#             */
/*   Updated: 2024/04/25 22:09:20 by antosanc         ###   ########.fr       */
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

static char	*expander_process(char *str, t_token **token)
{
	char	*expanded_str;
	char	*env_key;
	char	*env_value;
	int		l;
	int		i;

	i = 0;
	if (!((ft_isalnum(str[i + 1]) || str[i + 1] == '_') && str[i + 1]))
		return (str);
	l = 1;
	while ((ft_isalnum(str[i + l]) || str[i + l] == '_') && str[i + l])
		l++;
	env_key = ft_substr(str + i, 1, l - 1);
	env_value = get_env_value(env_key, (*token)->envp);
	free(env_key);
	expanded_str = create_expanded_str(str, env_value, token);
	free(env_value);
	return (expanded_str);
}

char	*expander(char *str, t_token **token)
{
	char	*expanded_str;
	int		i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] && !(str[i + 1] == '?'))
		expanded_str = expander_process(str, token);
	else
		expanded_str = create_expanded_str(str, ft_itoa(g_signal), token);
	free(str);
	return (expanded_str);
}
