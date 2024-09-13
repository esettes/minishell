/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:04:03 by uliherre          #+#    #+#             */
/*   Updated: 2024/09/13 12:43:02 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_token_lst
{
	char				*content;
	int					quotes;
	struct s_token_lst	*next;
}		t_token_lst;

typedef struct s_delimit
{
	int	start;
	int	end;
}		t_delimit;

typedef struct s_token
{
	int			i;
	char		**envp;
	t_token_lst	*token_lst;
	int			single_arg;
	int			*nextto;
	int			n_cmds;
	t_delimit	limit;
}	t_token;

//List utils
t_token 	*token_init(char **envp);
t_token_lst	*token_new(void);
t_token_lst	*token_last(t_token_lst *lst);
void		token_add_back(t_token_lst **lst, t_token_lst *new);
void		token_clear(t_token_lst **lst, void (*del)(void *));

t_cmd		*parser(char *str, char **envp, char *newbuff);

//Lex
t_token		*lex_tony(char *str, char **envp, char *newbuff, int n_cmds);
t_token_lst	*store_syntax_char(char *str, t_token *token);
int			check_syntax_char(char c);
void		*clear_all(t_token **token, char *error);
int			check_heredoc(t_token_lst *token_lst);
t_token_lst	*create_token_lst(char *str, int j, t_token **token, int flag);
t_token_lst	*create_token_lst_single(char *str, int j, t_token **token, int flag);

//Expander
char		*expander(char *str, char **envp, t_token **token);
int			len_expanded_str(char *str, char *env_value);
char		*get_env_value(char *var_env, char **envp);

//Validator
int			validator_tony(t_token *token);

//Yacc
t_cmd		*yacc_tony(t_cmd *cmd, t_token_lst **token_lst, char **envp);
int			count_cmd(t_token_lst *token_lst);
int			count_scmd_args(t_token_lst *token_lst);
void		free_scmd_tony(t_cmd *cmd);
void		free_cmd_tony(t_cmd *cmd);
void		open_file_parse(t_scmd *scmd);

//Heredoc
int	heredoc_init(t_scmd *scmd, t_token_lst **token_lst, char **envp);

/////

//void	get_cwd(char *old_cwd);
#endif
