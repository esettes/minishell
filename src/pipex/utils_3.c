/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:38:33 by antosanc          #+#    #+#             */
/*   Updated: 2024/09/03 18:43:18 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_simple_envp(t_pipe *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	data->env_mini = create_new_var(data,
		"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:"
			"/usr/bin:/sbin:/bin:/home/ubuntu/.local/bin");
	data->env_mini = create_new_var(data, "PWD=");
	change_var_value(data->env_mini, f_strjoin("PWD=", cwd));
	free(cwd);
}

/**
 * It doesnt free all allocated elems; saves buffer in oldbuffer and frees the
 * first one.
 * Frees and points to NULL childs, 
 * Reset with 0 or -1 values the non allocated elems
 */
void	reset_pipe_struct(t_pipe *p)
{
	//free_memory(p->env_mini, get_array_size(p->env_mini));
	if (p->childs)
	{
		free(p->childs);
		p->childs = NULL;
	}
	if (p->buff->oldbuffer)
		free(p->buff->oldbuffer);
	p->buff->oldbuffer = ft_strdup(p->buff->buffer);
	free(p->buff->buffer);
	p->buff->buffer = NULL;
	p->infile = 0;
	p->outfile = 0;
	p->pid = -1;
	p->pid2 = -1;
	p->std_[0] = 0;
	p->std_[1] = 0;
	p->n_cmds = 0;
	p->old_fd = 0;
	p->cmd_counter = 0;
}

/**
 * Free t_pipe totally
 */
void	free_pipe_struct(t_pipe *p)
{
	free_memory((const char **)p->env_mini, get_array_size(p->env_mini));
	if (p->childs)
		free(p->childs);
	if (p->buff->buffer)
		free(p->buff->buffer);
	if (p->buff->oldbuffer)
		free(p->buff->oldbuffer);
	free(p->buff);
	free(p);
}
