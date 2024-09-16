/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:03:59 by iostancu          #+#    #+#             */
/*   Updated: 2024/09/16 18:06:46 by settes           ###   ########.fr       */
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

// utils
t_pipe	init_struct(void);
void		free_dp(char **dp);
int			cmd_counter(char **all_cmd);
char		*f_find_path(char *cmd, t_list **env);
int			is_blank_line(char *line);
char		*nested_shell(char *line, char *keyword);
char		*ft_getenv(t_list **env, char *name, char *value);
void		ft_lstdelnode(t_list **head, t_list *node, t_list *tmp);
int			quotes_closed(char *line, int i, char quote);
char		*append_str(t_list **head);
int			check_syntax(t_list **env, char **new_vars);
void		replace_var(t_list **env, char *rep_var, char *var_name);
int			exit_status(int value);
char		*append_from_input(char *old_line, int fd);

// restore metachars
char		*reset_pipes(char *line);
char		*reset_vars(char *line);
char		*reset_quotes(char *line);
char		**reset_spaces(char **line);
char		*remove_quotes_metachar(int *i, int j, char *line, int quote);

// cmds
void		exec_pwd(void);
int			exec_cd(char **cmd);
void		exec_echo(char **word);
void		exec_env(t_list **environ);
t_list		**exec_export(t_list **env, char **new_vars);
int			run_execve(t_pipe *rl, char *abs_path, char **cmd);
t_list		**exec_unset(t_list **env, char **name);
void		exec_export_no_args(t_pipe **data);

//pipes
void		red_pipe_child(t_pipe *rl, int i);
void		run_executer(t_pipe *rl);
void		exec_single_cmd(t_pipe *rl);
void		exec_multiple_cmds(t_pipe *rl);
void		exec_single_cmd(t_pipe *rl);
void		close_fds(t_pipe *rl);
void		process_waiting(t_pipe *rl);

// check_files
int			redir_files(t_pipe *rl, char *cmd_line);
int			manage_line(t_pipe *rl, char *cmd_line, int i);
char		*quotes_checker(char *line);
char		**struct_quotes(char *old_cmd);
char		**expand_metachar(t_pipe *rl, char **rev_cmd);
char		**lst_to_arr(t_list **head);
char		*reset_metachar(char *line, int control);
void		here_doc(t_pipe *rl, char *keyword);
void		close_fd(t_pipe *rl);
void		print_err_msg(char c);
int			f_perror(int code, char *name);

// debug
char		*manage_pipe(char *line, int *i);

#endif
