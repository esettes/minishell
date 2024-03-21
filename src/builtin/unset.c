#include "../../inc/headers/minishell.h"

/*
static void unset_function(char **env, const char *unset_var)
{
	size_t	pos;
	size_t	tam;

	pos = search_in_env(env, unset_var);
	tam = env_len(env);
	free(env[pos]);
	while (pos < tam)// NEED TESTED 
	{
		env[pos] = env[pos + TRUE];
		pos++;
	}
	env[pos] = NULL;
}


int	unset_handler(char **env, const char *unset_var)
{
	if (NULL == env || NULL == *env || NULL == unset_var || NULL == *unset_var)
		return (EXIT_FAILURE);
	if (getenv(unset_var))
		unset_function(env, unset_var);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
*/
