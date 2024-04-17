#include "minishell.h"

/*
static int	is_builtin()
{

	return (EXIT_FAILURE);
}

static int	run_parent()
{

	return (EXIT_SUCCESS);
}

static int	run_child()
{
	close(data->pip[0]);
	if (open_file(cmd, &(*p_data)->infile, &(*p_data)->outfile))
		return (EXIT_FAILURE);
	if (infile > -1)
		if (duplicate_fd(infile, STDIN_FILENO))
			return (EXIT_FAILURE);
	if (duplicate_fd(data->pip[1], STDOUT_FILENO))
		return (EXIT_FAILURE);
	if (exec_process(data->cmd, envp, data->envp))
		return (EXIT_FAILURE);
	close((*p_data)->pip[1]);
	close((*p_data)->infile);
	(*p_data)->infile = (*p_data)->pip[0];
	return (EXIT_SUCCESS);
}

static int	fork_process()
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (fterror("fork = -1"), EXIT_FAILURE);
	if (pid == 0) 
	{
		if (run_child())
			exit (ft_puterror("execve fail"), EXIT_FAILURE);
	}
	else 
	{
		if (pipe((*p_data)->pip) < 0)
			return (ft_puterror("pipe fail"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	run_last_process()
{

	return (EXIT_SUCCESS);
}

static int	core_executer(t_executer *e, t_cmd *cmd)
{
	int	i;


	i = ZERO;
	while ((cmd->n_scmd - 1) > i)
	{
		if (is_parent_exec(cmd->scmd[i]->args[0]))
		{
			if (run_parent(cmd->scmd[i]))
				return (EXIT_FAILURE);
		}
		else
		{
			if (fork_process(cmd->scmd[i]))
				return (EXIT_FAILURE);
		}
		i++;
	}
	if (is_parent_exec(cmd->scmd[i]->args[0]))
	{
		if (run_parent(cmd->scmd[i]))
			return (EXIT_FAILURE);
	}
	else
	{
		if (run_last_process(cmd->scmd[i]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	init_executer(t_executer *e)
{
	e->pip[0] = -1;
	e->pip[1] = -1;
	e->pid = -1;
	e->pid2 = -1;
	e->cmd = NULL;
	e->last_cmd = NULL;
	e->infile = -1;
	e->outfile = -1;
}

int	executer(t_cmd *cmd, char **envp)
{
	t_executer	data;

	if (cmd->n_scmd < 1 || NULL == envp)
		return (f_error());
	init_executer(&data);
	data.envp = envp;
	if (core_executer(&data, cmd))
		return (ft_puterror("core_executer = -1"), EXIT_FAILURE);
	

	return (EXIT_SUCCESS);
}

*/
