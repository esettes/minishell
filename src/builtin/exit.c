#include "../../inc/headers/minishell.h"

int	exit_handler(t_cmd *cmd)
{
	printf("exit\n");
	free_cmd(&cmd);
	exit (EXIT_SUCCESS);
}
