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
	while ((ft_isalnum(str[i]) || str[i] == '_') && str[i])
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


/*manejar caso en que $ no le sigue nada porque me esta devolviendo /bin/bash que es la primera variable que se encuentra
y verificar el caso en el que se pone $? porque no esta funcionando igual que en bash*/
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
	if (env_value == NULL)
    	env_value = strdup("");
	free(env_key);
	expanded_str = create_expanded_str(str, env_value);
	free(env_value);
	free(str);
	return (expanded_str);
}