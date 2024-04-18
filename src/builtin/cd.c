/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:43:21 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/17 22:46:05 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cd	init_cd(t_pipe *data);
void	change_and_create_env_var(t_pipe **data, char *curr_dir);
void	is_home_directory(t_cmd *cmd, t_cd *cd);
char	*set_home_directory(t_pipe *data);

int	exec_cd(t_pipe *data, t_cmd *cmd, int pos)
{
	t_cd	cd;

	cd = init_cd(data);
	cd.dir_to_exec = cmd->scmd[pos]->args[1];
	is_home_directory(cmd, &cd);
	if (cd.dir_to_exec && f_strncmp(cd.dir_to_exec, "-", 1) == 0)
	{
		cd.is_hyphen = 1;
		if (!cd.last_dir)
		{
			ft_putstrc_fd(RED_, "minishell: cd: OLDPWD not set\n", 2);
			return (EXIT_SUCCESS);
		}
		cd.dir_to_exec = cd.last_dir;
	}
	if (cd.is_home)
		cd.dir_to_exec = set_home_directory(data);
	if (chdir(cd.dir_to_exec) < 0)
		return (f_error());
	if (cd.is_hyphen)
		printf("%s\n", cd.last_dir);
	change_and_create_env_var(&data, cd.curr_dir);
	return (EXIT_SUCCESS);
}

void	change_and_create_env_var(t_pipe **data, char *curr_dir)
{
	if (!env_var_already_exist((*data)->envp_minish, "OLDPWD="))
		//(*data)->envp_minish = 
		create_new_var((*data)->envp_minish, "OLDPWD=");
	change_var_value((*data)->envp_minish, f_strjoin("OLDPWD=", curr_dir));
	change_var_value((*data)->envp_minish, f_strjoin("PWD=", getcwd(NULL, 0)));
}

void	is_home_directory(t_cmd *cmd, t_cd *cd)
{
	if (cmd->scmd[0]->in_f || !(cd->dir_to_exec) || (cd->dir_to_exec
			&& f_strncmp(cd->dir_to_exec, "~", 1) == 0))
		cd->is_home = 1;
}

char	*set_home_directory(t_pipe *data)
{
	printf("HOME: '%s'\n", get_env_var_value(data->envp_minish, "HOME"));
	return (get_env_var_value(data->envp_minish, "HOME"));
}

t_cd	init_cd(t_pipe *data)
{
	t_cd	cd;

	cd.last_dir = get_env_var_value(data->envp_minish, "OLDPWD");
	cd.curr_dir = getcwd(NULL, 0);
	cd.is_hyphen = 0;
	cd.is_home = 0;
	cd.dir_to_exec = NULL;
	return (cd);
}
