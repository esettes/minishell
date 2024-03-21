#include "../../inc/headers/minishell.h"

static int	add_last_env(char **env, const char *export_var)
{
	register size_t	x;

	x = env_len(env);
	env[x] = ft_strdup(export_var);
	if (NULL == env[x])
		return (EXIT_FAILURE);
	env[x + TRUE] = NULL;
	return (EXIT_SUCCESS);
}

static int	add_env_pos(char **env, const char *export_var, char *var_name)
{
	size_t	pos;

	pos = search_in_env(env, var_name);
	free(var_name);
	free(env[pos]); /* NEED TESTED */
	env[pos] = ft_strdup(export_var);
	if (NULL == env[pos])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	export_handler(char **env, const char *export_var)
{
	char	*delimiter;
	char	*var_name;

	if (NULL == env || NULL == *env || NULL == export_var || 0 == *export_var)
		return (EXIT_FAILURE);
	delimiter = strchr(export_var, '=');
	if (NULL == delimiter)
		return (EXIT_FAILURE);
	var_name = ft_substr(export_var, ZERO, delimiter - export_var); /* NEED TESTED */
	if (NULL == var_name)
		return (EXIT_FAILURE);
	/* MAYBE NEED DUPLICATE ENV*/
	if (getenv(var_name))
	{
		if (add_env_pos(env, export_var, var_name))
			return (EXIT_FAILURE);
	}
	else
	{
		if (add_last_env(env, export_var))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
