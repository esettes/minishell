#include "../../inc/headers/minishell.h"

static t_scmd	*build_scmd(t_list **lst)//need improve
{
	t_scmd	*new;
	t_list	*start;
	char	*aux;
	int		i;

	new = (t_scmd *)ft_calloc(TRUE, sizeof(t_scmd));
	if (NULL == new)
		return (NULL);
	aux = NULL;
	i = ZERO;
	start = *lst;
	while (*lst && NULL == aux)
	{
		aux = ft_strnstr("|", (char *)(*lst)->content, sizeof("|"));
		*lst = (*lst)->next;
		if (aux == NULL)
			i++;
		else
			break ;
	}
	insert_args(&new, start, &i);
	return (new);
}

t_cmd	*yacc(t_cmd *cmd, t_list *lst)
{
	t_scmd	*aux;
	t_list	*start;

	cmd->n_scmd = scommand_count(lst);
	cmd->scmd = (t_scmd **)ft_calloc((cmd->n_scmd + TRUE), sizeof(t_scmd *));
	if (NULL == cmd->scmd)
		return (NULL);
	start = lst; // MAYBE NOT NECESARY
	while (lst && cmd->n_available_scmd < cmd->n_scmd)
	{
		aux = build_scmd(&lst);
		if (NULL == aux)
			return (free(cmd), NULL);
		insert_scmd(cmd, aux);
	}
	lst = start; // MAYBE NOT NECESARY
	return (cmd);
}
