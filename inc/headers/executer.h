#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"

typedef struct s_executer
{
	int		fd[2];
	pid_t	pid;
	pid_t	pid2;
	char	*envp;
	int		infile;
	int		outfile;
}	t_executer;

#endif
