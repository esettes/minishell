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

static char	*create_expanded_str(char *str, char *env_value)
{
	char	*array;
	int		len;

	len = len_expanded_str(str, env_value);
	array = (char *)malloc(len + 1);
	if (!array)
	{
		free(str);
		free(env_value);
		exit(EXIT_FAILURE);
	}
	return (fill_array(str, env_value, array));
}

static char	*get_env_value(char *var_env, char **envp)
{
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(var_env, envp[i], ft_strlen(var_env)) == 0
			&& envp[i][ft_strlen(var_env)] == '=')
		{
			j = 0;
			while (envp[i][j] != '=' && envp[i][j])
				j++;
			if (envp[i][j + 1])
			{
				free(var_env);
				return (ft_substr(envp[i] + j, 1,
						ft_strlen(envp[i]) - (j + 1)));
			}
		}
		i++;
	}
	return (strdup(""));
}

char	*expander_process(char *str, char **envp)
{
	char	*expanded_str;
	char	*env;
	int		l;
	int		i;

	i = 0;
	while (str[i] != '$' && str[i])
		i++;
	if (!(str[i + 1] == '?'))
	{
		if (!((ft_isalnum(str[i + 1]) || str[i + 1] == '_') && str[i + 1]))
			return (str);
		l = 1;
		while ((ft_isalnum(str[i + l]) || str[i + l] == '_') && str[i + l])
			l++;
		env = ft_substr(str + i, 1, l - 1);
		env = get_env_value(env, envp);
		expanded_str = create_expanded_str(str, env);
		free(env);
	}
	else
		expanded_str = create_expanded_str(str, ft_itoa(g_signal));
	free(str);
	return (expanded_str);
}
