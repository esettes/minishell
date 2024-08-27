/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:07:46 by iostancu          #+#    #+#             */
/*   Updated: 2024/08/28 00:17:53 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

typedef struct s_cd
{
	char	*curr_dir;
	char	*last_dir;
	size_t	is_hyphen;
	size_t	is_home;
	int		infile;
	char	*dir_to_exec;
	int		bytes;
	int		stdin_;
}	t_cd;

/** 
 * @brief t_unset
 * 
 * @var t_unset::i
 * @var t_unset::j
 * @var t_unset::k
 */
typedef struct s_unset
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**tmp;
	size_t	arr_size;
	char	*var;
}	t_unset;

int		exec_echo(t_scmd scmd);
int		exec_exit(t_cmd *cmd, t_pipe *d);
char	*ft_getenv(char **envp, char *var_name);
int		exec_cd(t_pipe *data, t_cmd *cmd, int pos);
int		exec_env(t_pipe *data);
int		init_envp_minishell(t_pipe *data, char *envp[]);
int		exec_export(t_pipe *data, t_cmd *cmd, int pos);
int		exec_unset(t_cmd *cmd, t_pipe *data, int pos);
size_t	get_array_size(char **arr);
int		env_var_already_exist(char **envp_minish, char *raw_variable);
size_t	get_array_size(char **arr);
char	*get_env_variable(char *var);
int		is_correct_env_variable(char *var, char *cmd);
char	*get_env_var_value(char **envp_minish, char *var);
int		exec_pwd(char *old_cwd);
char	**create_new_var(t_pipe *data, char *var);
void	print_cmd_error(char *var, char *cmd);
int		change_var_value(char **envp_minish, char *raw_variable);
/**
 * @brief Get the env variable from the minishell environment
 * 
 * @param var_value 
 * @param var 
 * @return char* 
 */
char	*get_env_variable_from_minish_environ(char **envp_minish, char *var);
void	init_env(char **env, size_t len, char **envp_minish);
void	print_env_not_set(char *cmd, char *var);
void	print_err_msg(char *cmd, char *var, char *msg);
int		get_num_scmd_args(t_scmd scmd);

#endif
