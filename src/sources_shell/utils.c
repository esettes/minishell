#include "minishell.h"

char	**lst_to_arr(t_list **head)
{
	t_list	*node;
	char	**array;
	int		i;

	i = 0;
	node = *head;
	array = malloc(sizeof(char *) * (ft_lstsize(node) + 1));
	while (node)
	{
		array[i++] = ft_strdup(node->content);
		node = node->next;
	}
	array[i] = 0;
	return (array);
}

t_list	**cpy_env(void)
{
	extern char	**environ;
	t_list		**new_env;
	int			i;

	i = -1;
	new_env = malloc(sizeof(t_list **));
	*new_env = 0;
	while (environ[++i])
		ft_lstadd_back(new_env, ft_lstnew(ft_strdup(environ[i])));
	return (new_env);
}

void	none(int sig)
{
	(void) sig;
	return ;
}

t_pipe	init_struct(void)
{
	t_pipe	data;
	extern FILE	*stderr;

	rl_outstream = stderr;
	rl_catch_signals = 0;
	ft_memset(&data, 0, sizeof(t_pipe));
	data.env = cpy_env();
	signal(SIGQUIT, none);
	return (data);
}
