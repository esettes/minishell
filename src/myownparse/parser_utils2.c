#include <minishell.h>

static char	*remove_quotes(char *str)
{
	int		n_quotes;
	char	*ret;
	int		i;
	int		j;

	i = -1;
	j = 0;
	n_quotes = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			n_quotes++;
	}
	ret = malloc(sizeof(char) * ((ft_strlen(str) - n_quotes )+ 1));
	i = 0;
	while (str[i])
	{
		if (str[i] != '"')
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	//free (str);
	//ft_memset(str, 0, sizeof(str));
	//str = ft_strdup(ret);
	//free(ret);
	ft_strlcpy(str, ret, sizeof(ret+ 2));
	return (ret);
}

void	set_single_arg_token(t_token **token, t_token_lst *t_list)
{
	if (t_list && t_list->content && *t_list->content
			|| t_list && t_list->quotes == 1)
			token_add_back(&(*token)->token_lst, t_list);
		if (token == NULL)
			return ;
}
