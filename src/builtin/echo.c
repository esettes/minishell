#include "../../inc/headers/minishell.h"

int echo_handler(t_scmd scmd)
{
	size_t	x;
	int		flag;

	x = ZERO;
	flag = TRUE;
	while (x < (size_t)scmd.argc && scmd.args[x + TRUE] 
			&& !ft_strncmp(scmd.args[x + TRUE], "-n", sizeof("-n")))
	{
		flag = FALSE;
		x++;
	}
	while (x < (size_t)scmd.argc && scmd.args[x + TRUE])
	{
		ft_putstr_fd(scmd.args[x + TRUE], STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		x++;
	}
	if (flag)
		write (STDOUT_FILENO, "\n", sizeof(char));
	return (EXIT_SUCCESS);
}
