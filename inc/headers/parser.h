/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:04:03 by uliherre          #+#    #+#             */
/*   Updated: 2024/04/23 23:47:23 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define ERR_PIPE "syntax error near unexpected token `|\'"
# define ERR_REDIRECT "syntax error near unexpected token `< / >\'"
# define ERR_NEWLINE "syntax error near unexpected token `newline\'"

typedef struct s_expander
{
	char	*expanded;
	char	*var;
	char	*index;
	char	*aux;
	char	*auxvar;
}			t_expander;



t_cmd	*parser(char *str, char **envp);
t_list	*lex(char *str, char **envp);
char	*expander(char *str, char **envp);
int		validator(t_list *tokens);
t_cmd	*yacc(t_cmd *cmd, t_list *lst);

void	free_cmd(t_cmd **cmd);
void	free_scmd(t_scmd **scmd);
void	insert_scmd(t_cmd *cmd, t_scmd *scmd);
void	insert_args(t_scmd **scmd, t_list *args, int *i);
int		scommand_count(t_list *lst);
size_t	val_get_type(char *token);
void	redirect_phase(t_scmd *scmd, t_list **tokens, int *i);

//parse Tony

typedef struct s_token_lst
{
	char				*content;
	int					quotes;
	struct s_token_lst	*next;
}		t_token_lst;

typedef struct s_token
{
	int			i;
	char		**envp;
	t_token_lst	*token_lst;
}	t_token;

//List utils
t_token 	*token_init(char **envp);
t_token_lst	*token_new(void);
t_token_lst	*token_last(t_token_lst *lst);
void		token_add_back(t_token_lst **lst, t_token_lst *new);
void		token_clear(t_token_lst **lst, void (*del)(void *));

t_cmd		*parser(char *str, char **envp);

//Lex
t_token		*lex_tony(char *str, char **envp);
char		*expander_process(char *str, t_token *token);
t_token_lst	*store_syntax_char(char *str, t_token *token);
int			check_syntax_char(char c);
void		*clear_all(t_token *token, char *error);
int			check_heredoc(t_token_lst *token_lst);
t_token_lst	*create_token_lst(char *str, int j, t_token *token, int flag);

//Validator
int			validator_tony(t_token *token);

//Yacc
t_cmd		*yacc_tony(t_cmd *cmd, t_token_lst **token_lst);
int			count_cmd(t_token_lst *token_lst);
int			count_scmd_args(t_token_lst *token_lst);
void		free_scmd_tony(t_cmd *cmd);
void		free_cmd_tony(t_cmd *cmd);

//Heredoc
int			heredoc_init(t_scmd *scmd, t_token_lst **token_lst);

#endif