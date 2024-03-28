/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:04:03 by uliherre          #+#    #+#             */
/*   Updated: 2024/03/28 12:44:59 by ubuntu           ###   ########.fr       */
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

#endif
