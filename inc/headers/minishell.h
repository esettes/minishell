/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:03:59 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/16 20:30:57 by iostancu         ###   ########.fr       */
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
# include "../libft/inc/libft.h"
# include "pipex.h"
# include "parser.h"
# include "structs.h"
# include "builtin.h"

# include <readline/readline.h>
# include <readline/history.h>

extern int	g_signal;

int	core_shell(char **envp);
int	NEW_core_shell(char **envp);

#endif
