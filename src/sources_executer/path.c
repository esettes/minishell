#include "minishell.h"

char	*get_path(char *cmd, char *path_envp)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	paths = ft_split(path_envp, ':');
	i = 0;
	while (paths[i])
	{
		tmp = f_strjoin(paths[i], "/");
		path = f_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
		{
			free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

int	cmd_have_path(char *cmd)
{
	register int	i;

	i = 0;
	while (cmd[i])
		if (cmd[i++] == '/')
			return (TRUE);
	return (FALSE);
}

int	cmd_have_current_path(char *cmd)
{
	register int	i;

	i = 0;
	while (cmd[i])
		if (cmd[i++] == '.')
			return (TRUE);
	return (FALSE);
}
