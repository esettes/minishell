/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:43:21 by iostancu          #+#    #+#             */
/*   Updated: 2024/08/31 01:20:41 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cd	init_cd(t_pipe *data, t_cmd *cmd, int pos);
static void	change_and_create_env_var(t_pipe **data, char *curr_dir);
static void	is_home_directory(t_cmd *cmd, t_cd *cd);
static char	*set_home_directory(t_pipe *data);

static void	error_case(t_cd *cd, char *cmd, char *var)
{
	free(cd->curr_dir);
	print_env_not_set(cmd, var);
}

int	exec_cd(t_pipe *data, t_cmd *cmd, int pos)
{
	t_cd	cd;

	if (get_num_scmd_args(*cmd->scmd[pos]) > 2)
	{
		print_err_msg("cd", "", "too many arguments.\n");
		return (EXIT_FAILURE);
	}
	cd = init_cd(data, cmd, pos);
	is_home_directory(cmd, &cd);
	if (cd.dir_to_exec && f_strncmp(cd.dir_to_exec, "-", 1) == 0)
	{
		cd.is_hyphen = 1;
		if (!cd.last_dir)
			return (error_case(&cd, "cd", "OLDPWD"), EXIT_SUCCESS);
		cd.dir_to_exec = cd.last_dir;
	}
	if (cd.is_home)
		cd.dir_to_exec = get_env_var_value(data->env_mini, "HOME");
	if (cd.is_home && (!env_var_already_exist(data->env_mini, "HOME=")))
		return (error_case(&cd, "cd", "HOME"), EXIT_SUCCESS);
	if (chdir(cd.dir_to_exec) < 0)
	{
		exit_s = 2;
		//printf("minishell: cd: %s: No such file or directory.\n", cd.dir_to_exec);
		//return (free(cd.curr_dir), EXIT_FAILURE);
		return (f_error(data));
	}
	if (cd.is_hyphen)
		printf("%s\n", cd.last_dir);
	change_and_create_env_var(&data, cd.curr_dir);
	free(cd.curr_dir);
	return (EXIT_SUCCESS);
}

static void	change_and_create_env_var(t_pipe **data, char *curr_dir)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		print_err_msg("cd", "", "error retrieving current directory: getcwd: cannot access"
			"parent directories: No such file or directory\n");
		return ;
	}
	if (!env_var_already_exist((*data)->env_mini, "OLDPWD="))
		(*data)->env_mini = create_new_var(*data, "OLDPWD=");
	change_var_value((*data)->env_mini, f_strjoin("OLDPWD=", curr_dir));
	change_var_value((*data)->env_mini, f_strjoin("PWD=", cwd));
	free(cwd);
}

static void	is_home_directory(t_cmd *cmd, t_cd *cd)
{
	if (cmd->scmd[0]->in_f || !(cd->dir_to_exec) || (cd->dir_to_exec
			&& f_strncmp(cd->dir_to_exec, "~", 1) == 0))
		cd->is_home = 1;
}

static t_cd	init_cd(t_pipe *data, t_cmd *cmd, int pos)
{
	t_cd	cd;

	cd.last_dir = get_env_var_value(data->env_mini, "OLDPWD");
	cd.curr_dir = getcwd(NULL, 0);
	cd.is_hyphen = 0;
	cd.is_home = 0;
	cd.dir_to_exec = cmd->scmd[pos]->args[1];
	return (cd);
}
