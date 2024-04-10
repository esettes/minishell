#include "../../inc/headers/minishell.h"

int	pwd_handler(void)
{
	char	*buffer;

	buffer = getcwd(NULL, MAXPATHLEN);
	if (buffer)
	{
		ft_putendl_fd(buffer, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
