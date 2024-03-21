#include "../../inc/headers/minishell.h"

void	free_cmd(t_cmd **cmd)
{
	while (ZERO < (*cmd)->n_scmd)
	{
		free_scmd(&(*cmd)->scmd[(*cmd)->n_scmd - 1]);
		(*cmd)->n_scmd -= TRUE;
	}
	free((*cmd)->scmd);
	(*cmd)->scmd = NULL;
}

void	insert_scmd(t_cmd *cmd, t_scmd *scmd)
{
	cmd->scmd[cmd->n_available_scmd] = scmd;
	cmd->n_available_scmd += TRUE;
}

int	scommand_count(t_list *lst)
{
	register int	scommand_count;

	scommand_count = TRUE;
	while (NULL != lst)
	{
		if (ZERO == ft_strncmp(lst->content, "|", sizeof("|")))
			scommand_count++;
		lst = lst->next;
	}
	return (scommand_count);
}
