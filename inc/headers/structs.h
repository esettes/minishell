/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:43:08 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/10 20:56:47 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define EXIT_	"exit"

# define T_REDIRECT 1
# define T_PIPE 2
# define T_QUOTE 3
# define T_WORLD 4

typedef struct s_scmd
{
	int			n_available_args;
	int			argc;
	char		**args;
	char		*in_f;
	char		*out_f;
	int			append;
}				t_scmd;

typedef struct s_cmd
{
	int			n_available_scmd;
	int			n_scmd;
	t_scmd		**scmd;
}				t_cmd;

typedef struct s_prompt
{
	char	*curr_dir;
	char	*home_substr;
	char	*join_usr_color;
	char	*join_usr_curr_dir;
	char	*usr;
	char	*prompt;
}				t_prompt;

#endif
