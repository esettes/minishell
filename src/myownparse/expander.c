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

static char	*create_expanded_str(char *str, char *env_value)
{
	char	*array;
	int		len;
	int		i;
	int		j;
	int		x;

	len = len_expanded_str(str, env_value);	
	array = (char *)malloc(len + 1);
	i = 0;
	j = 0;
	x = 0;
	if (!array)
	{
		free(str);
		free(env_value);
		//falta hacer el exit pero no se como aun
	}
	while (str[i] != '$' && str[i])
		array[j++] = str[i++];
	while ((ft_isalnum(str[i]) || str[i] == '_') && str[i])
		i++;
	while (env_value[x])
		array[j++] = env_value[x++];
	while (str[i])
		array[j++] = str[i++];
	array[j] = '\0';
	return (array);	
}

static char	*get_env_value(char *var_env, char **envp)
{
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(var_env, envp[i], ft_strlen(var_env)) == 0)
		{
			j = 0;
			while (envp[i][j] != '=' && envp[i][j])
				j++;
			if (envp[i][j + 1])
				return (ft_substr(envp[i] + j, 1, ft_strlen(envp[i]) - (j + 1)));
		}
		i++;
	}
	return (NULL);
}

char	*expander_process(char *str, char **envp)
{
	char	*expanded_str;
	char	*env_value;
	char	*env_key;
	int		len;
	int		i;

	i = 0;
	while (str[i] != '$' && str[i])
		i++;
	if (str[i + 1] == '?')
	{
		free(str);
		return (ft_itoa(g_signal));
	}
	len = 1;
	while ((ft_isalnum(str[i + len]) || str[i + len] == '_') && str[i + len])
		len++;
	env_key = ft_substr(str + i, 1, len - 1);
	env_value = get_env_value(env_key, envp);
	free(env_key);
	expanded_str = create_expanded_str(str, env_value);
	free(env_value);
	free(str);
	return (expanded_str);
}