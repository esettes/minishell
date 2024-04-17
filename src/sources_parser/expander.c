#include "../../inc/headers/minishell.h"

static char	*search_end_env_var(char *env_var)
{
	size_t	x;

	x = TRUE;
	while (env_var[x] && (ft_isalnum(env_var[x]) || '_' == env_var[x]))
		++x;
	return (&env_var[x]);
}

char	*ft_getenv(char **envp, char *var_name)
{
	size_t	x;
	size_t	tam;

	x = ZERO;
	tam = ft_strlen(var_name);
	while (envp[x])
	{
		if (!ft_strncmp(var_name, envp[x], tam) && '=' == envp[x][tam])
			return (&envp[x][tam + TRUE]);
		++x;
	}
	return (NULL);
}

static char	*expand_dollar(char *expand, char **envp)
{
	char	*expanded_value;
	char	*var_name;
	char	*end_var;

	end_var = search_end_env_var(expand);
	//printf("end_var: [%s]\n", end_var);
	if (f_strncmp("?", end_var, sizeof("?")) == 0)
	{
		//printf("g_signal: %d\n", g_signal);
		return (ft_itoa(g_signal));//leak
	}
	var_name = ft_substr(expand, TRUE, end_var - expand - 1);
	//printf("var_name: [%s]\n", var_name);
	expanded_value = ft_getenv(envp, var_name);
	free(var_name);
	if (NULL == expanded_value)
		return (ft_strdup(""));
	else
		return (ft_strdup(expanded_value));
}

static char	*expand_dollars_handler(char *str, char **envp)
{
	t_expander	e;

	e.expanded = ft_strdup("");
	e.index = str;
	while (*str)
	{
		e.index = ft_strchr(e.index, '$');
		if (!e.index || !*(e.index + 1))
			break ;
		if (str != e.index && '\\' == *(e.index - TRUE))
		{
			++(e.index);
			continue ;
		}
		e.aux = ft_substr(str, ZERO, e.index - str);
		e.var = expand_dollar(e.index, envp);
		e.auxvar = ft_strjoin_f1_f2(e.aux, e.var);
		e.expanded = ft_strjoin_f1_f2(e.expanded, e.auxvar);
		str = search_end_env_var(e.index);
		e.index = search_end_env_var(e.index);
	}
	e.expanded = ft_strjoin_f1(e.expanded, str);
	return (e.expanded);
}

char	*expander(char *str, char **envp)
{
	char	*expanded;
	char	*aux;

	if ('\'' == *str)
		expanded = ft_substr(str, TRUE, ft_strlen(str) - 2);
	else if ('\"' == *str)
	{
		aux = expand_dollars_handler(str, envp);
		expanded = ft_substr(aux, TRUE, ft_strlen(aux) - 2);
		free(aux);
	}
	else
		expanded = expand_dollars_handler(str, envp);
	return (free(str), expanded);
}
