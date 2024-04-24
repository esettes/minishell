/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:43:08 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/19 21:37:45 by antosanc         ###   ########.fr       */
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

typedef struct s_buff
{
	char	*buffer;
	char	*oldbuffer;
}				t_buff;

#endif
