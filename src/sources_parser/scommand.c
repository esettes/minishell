#include "../../inc/headers/minishell.h"

void	free_scmd(t_scmd **scmd)
{
	while (ZERO <= (*scmd)->argc)
	{
		free((*scmd)->args[(*scmd)->argc]);
		(*scmd)->args[(*scmd)->argc] = NULL;
		(*scmd)->argc -= TRUE;
	}
	free((*scmd)->args);
	(*scmd)->args = NULL;
	free((*scmd)->in_f);
	free((*scmd)->out_f);
	(*scmd)->in_f = NULL;
	(*scmd)->out_f = NULL;
	free(*scmd);
	*scmd = NULL;
}

void	insert_args_old(t_scmd *scmd, t_list **args, int argc)
{
	scmd->args[ZERO] = ft_strdup((*args)->content);
	*args = (*args)->next;
	while (ZERO != argc-- && args)
	{
		scmd->args[scmd->n_available_args + TRUE] = ft_strdup((*args)->content);
		*args = (*args)->next;
		scmd->n_available_args += TRUE;
	}
	scmd->args[scmd->n_available_args + TRUE] = NULL;
}

void	insert_args(t_scmd **scmd, t_list *args, int *i)
{
	t_list	*aux;
	size_t	count;

	while (*i)
	{
		if (T_REDIRECT == val_get_type(args->content))
			redirect_phase(*scmd, &args, i);
		else if (args && T_WORLD == val_get_type(args->content))
		{
			aux = args;
			count = ZERO;
			while (T_WORLD == val_get_type(aux->content))
			{
				count++;
				*i -= TRUE;
				aux = aux->next;
				if (NULL == aux)
					break;
			}
			(*scmd)->argc = count - TRUE;
			(*scmd)->args = ft_calloc(count + TRUE, sizeof(char *));
			insert_args_old(*scmd, &args, count - TRUE);
		}
	}
}
