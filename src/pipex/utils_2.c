/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:30:58 by iostancu          #+#    #+#             */
/*   Updated: 2024/05/21 21:30:54 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_pipe	*init_pipe_struct(char *envp[])
{
	t_pipe	*tmp;

	tmp = malloc(sizeof(t_pipe));
	if (tmp == NULL)
		if (f_error())
			return (NULL);
	init_envp_minishell(tmp, envp);
	if (*tmp->envp_minish == NULL)
		create_simple_envp(tmp);
	tmp->envp = get_env_var_value(tmp->envp_minish, "PATH");
	tmp->cmd = NULL;
	tmp->infile = -1;
	tmp->outfile = -1;
	tmp->pid = -1;
	tmp->pid2 = -1;
	tmp->last_cmd = NULL;
	return (tmp);
}

int	open_file(t_cmd *cmd, t_pipe *data, int pos)
{
	if (cmd->scmd[pos]->in_f)
	{
		data->infile = open(cmd->scmd[pos]->in_f, O_RDONLY, 0644);
		if (data->infile < 0)
			return (print_err_msg(cmd->scmd[pos]->in_f, NULL, NULL));
	}
	else
		data->infile = -1;
	if (cmd->scmd[pos]->out_f)
	{
		if (cmd->scmd[pos]->append)
		{
			data->outfile = open(cmd->scmd[pos]->out_f,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else
			data->outfile = open(cmd->scmd[pos]->out_f,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->outfile < 0)
			return (f_error());
	}
	else
		data->outfile = -1;
	return (EXIT_SUCCESS);
}

void	close_files(int *infile, int *outfile)
{
	if (*infile > -1)
		close(*infile);
	if (*outfile > -1)
		close(*outfile);
}

int	dup_files(int *infile, int *outfile)
{
	if (*infile > -1)
		if (dup2(*infile, 0) < 0)
			return (f_error());
	if (*outfile > -1)
		if (dup2(*outfile, 1) < 0)
			return (f_error());
	return (EXIT_SUCCESS);
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
