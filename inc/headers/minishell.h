/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:03:59 by uliherre          #+#    #+#             */
/*   Updated: 2024/03/13 23:08:05 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>			/* Para printf */
# include <stdlib.h>		/* Para malloc, free */
# include <unistd.h>		/* Para write, access, open, read, close, fork, exit, getcwd, chdir */
# include <sys/wait.h>		/* Para wait, waitpid, wait3, wait4 */
# include <signal.h>		/* Para signal, sigaction, kill */
# include <sys/stat.h>		/* Para stat, lstat, fstat */
# include <fcntl.h>			/* Para unlink, execve, dup, dup2, pipe */
# include <dirent.h>		/* Para opendir, readdir, closedir */
# include <string.h>		/* Para strerror */
# include <errno.h>			/* Para perror */
# include <termios.h>		/* Para tcsetattr, tcgetattr */
# include <curses.h>		/* Para tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs */
# include <sys/param.h>
# include "libft.h"
# include "pipex.h"
# include "ft_printf.h"
# include "parser.h"
# include "structs.h"
# include "executer.h"
# include "builtin.h"

# include <readline/readline.h>
# include <readline/history.h>

extern volatile int	g_signal;

int	core_shell(char **envp);
int	NEW_core_shell(char **envp);

#endif
