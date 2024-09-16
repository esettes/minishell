#include "minishell.h"

void	swap_str(char **env, int i, int j)
{
	char	*tmp;

	tmp = env[i];
	env[i] = env[j];
	env[j] = tmp;
}

char	**free_arr(const char **arr, size_t pos)
{
	while (pos--)
		free ((void *)arr[pos]);
	free(arr);
	return (NULL);
}

int	get_array_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	exec_export_no_args(t_pipe **data)
{
	int     i;
    int     j;
	char	**env;
    int     len;

	env = lst_to_arr((*data)->env);
    len = get_array_size(env);
	i = -1;
	while (++i < len)
	{
		j = i;
		while (++j < len)
		{
			if (ft_strncmp(env[j], env[i],
					ft_strlen(env[i]) + ft_strlen(env[j])) < 0)
				swap_str(env, i, j);
		}
	}
	i = -1;
    while (++i < len)
        printf("declare -x %s\n", env[i]);
	free_arr((const char **)env, i);
}
