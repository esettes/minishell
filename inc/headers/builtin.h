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

typedef struct s_unset
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**tmp;
	size_t	arr_size;
	char	*var;
}	t_unset;

int		export_handler(char **env, const char *export_var);
int		unset_handler(char **env, const char *unset_var);
size_t	env_len(char **env);
int		echo_handler(t_scmd scmd);
int		exit_handler(t_cmd *cmd);
size_t	search_in_env(char **env, char *to_search);
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
char	*get_env_var_value(t_pipe *data, char *var);
int		pwd_handler(void);
char	**create_new_var(char **envp_minish, char *var);
int	change_var_value(char **envp_minish, char *raw_variable);
/**
 * @brief Get the env variable from the minishell environment
 * 
 * @param var_value 
 * @param var 
 * @return char* 
 */
char	*get_env_variable_from_minish_environ(char **envp_minish, char *var);

#endif
