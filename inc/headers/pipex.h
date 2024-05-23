/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:09:44 by iostancu          #+#    #+#             */
/*   Updated: 2024/05/23 21:46:42 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "sys/types.h"
# include "../../inc/headers/structs.h"

typedef struct s_pipe
{
	int		pip[2];
	pid_t	pid;
	pid_t	pid2;
	char	**cmd;
	char	**last_cmd;
	char	*envp;
	char	**envp_minish;
	int		infile;
	int		outfile;
	int		stdout_cpy;
}	t_pipe;

# define COLORED 1
# define R			0
# define W			1

# if COLORED
#  define RED_    "\x1b[31m"
#  define GREEN_  "\x1b[32m"
#  define YELLOW_ "\x1b[33m"
#  define BLUE_   "\x1b[34m"
#  define VIOLET_ "\x1b[35m"
#  define CYAN_   "\x1b[36m"
#  define RESET_  "\x1b[0m"
# else
#  define RED_    ""
#  define GREEN_  ""
#  define YELLOW_ ""
#  define BLUE_   ""
#  define VIOLET_ ""
#  define CYAN_   ""
#  define RESET_  ""
# endif

int		f_error(void);
/**
 * @brief Redirects the file descriptor oldfd to newfd.
 * 
 * @param oldfd
 * @param newfd
 */
int		duplicate_fd(int oldfd, int newfd);
int		exec_process(t_pipe *data, char **cmd);
int		run_child(t_pipe *data, t_cmd *cmd, int pos, char *old_cwd);
int		run_child2(t_pipe *data, t_cmd *cmd, int pos, char *old_cwd);
int		cmd_have_path(char *cmd);
int		cmd_have_current_path(char *cmd);
char	*get_path(char *cmd, char *path_envp);
void	free_split(char **s);
int		f_pipex(t_pipe *p_data, t_cmd *cmd, char *old_cwd);
void	ft_putstrc_fd(char *color, char *s, int fd);
char	*f_strdup(const char *s1);
int		f_strncmp(const char *s1, const char *s2, size_t n);
size_t	f_strlen(const char *s);
char	**f_split(char const *s, char c);
char	*f_strjoin(char const *s1, char const *s2);
int		f_strict_strncmp(const char *s1, const char *s2, size_t n);
void	create_simple_envp(t_pipe *data);
int		is_directory(char *path);

int		is_parent_exec(char *str);
int		run_parent(t_cmd *cmd, t_pipe **p_data, int pos, char *old_cwd);
t_pipe	*init_pipe_struct(char *envp[]);
/**
 * @brief Frees all the strings allocated in the double ptr, and then frees
 * the double ptr.
 * 
 * @param arr Array to free.
 * @param pos The size of the array.
 * @return char** NULL
 */
char	**free_memory(const char **arr, size_t pos);
int		open_file(t_cmd *cmd, t_pipe *data, int pos);
void	close_files(int *infile, int *outfile);
int		dup_files(int *infile, int *outfile);

#endif
