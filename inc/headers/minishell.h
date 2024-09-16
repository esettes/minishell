/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:03:59 by iostancu          #+#    #+#             */
/*   Updated: 2024/09/16 19:04:08 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>	
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/param.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <sys/signal.h>
# include <sys/types.h>
# include "../libft/inc/libft.h"

# include <readline/readline.h>
# include <readline/history.h>

# define SIMPLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define PIPE 124
# define LESS_THAN 60
# define MORE_THAN 62
# define APPEND 68
# define HERE_DOC 72
# define DOLLAR 36
# define BUF_SIZE 4096

typedef struct s_pipe
{
	char	*line;
	char	**all_cmd;
	t_list	**env;
	int		n_cmd;
	int		pipe[2];
	int		old_fd;
	int		infile;
	int		outfile;
	int		std_[2];
	int		status;
}	t_pipe;

t_pipe	init_struct(void);
void	free_dp(char **dp);
int		cmd_counter(char **all_cmd);
char	*f_find_path(char *cmd, t_list **env);
int		is_blank_line(char *line);
char	*ft_getenv(t_list **env, char *name, char *value);
void	ft_lstdelnode(t_list **head, t_list *node, t_list *tmp);
int		quotes_closed(char *line, int i, char quote);
char	*append_str(t_list **head);
int		check_syntax(t_list **env, char **new_vars);
void	replace_var(t_list **env, char *rep_var, char *var_name);
int		exit_status(int value);

char	*reset_pipes(char *line);
char	*reset_vars(char *line);
char	**reset_spaces(char **line);
char	*remove_quotes_metachar(int *i, int j, char *line, int quote);

void	exec_pwd(void);
int		exec_cd(char **cmd);
void	exec_echo(char **word);
void	exec_env(t_list **environ);
t_list	**exec_export(t_list **env, char **new_vars);
int		run_execve(t_pipe *data, char *abs_path, char **cmd);
t_list	**exec_unset(t_list **env, char **name);
void	exec_export_no_args(t_pipe **data);
t_list	**run_export(t_list **env, char **cmd, t_pipe **d);

void	run_executer(t_pipe *data);
void	exec_single_cmd(t_pipe *data);
void	exec_multiple_cmds(t_pipe *d);
void	close_fds(t_pipe *data);
void	process_waiting(t_pipe *data);

int		redir_files(t_pipe *data, char *cmd_line);
int		manage_line(t_pipe *data, char *cmd_line, int i);
char	*quotes_checker(char *line);
char	**expand_metachar(t_pipe *data, char **rev_cmd);
char	**lst_to_arr(t_list **head);
void	here_doc(t_pipe *data, char *keyword);
void	print_err_msg(char c);
int		f_perror(int code, char *name);
void	wait_cmds(t_pipe *data);

#endif
