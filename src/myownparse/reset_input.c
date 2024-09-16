#include "minishell.h"

char	**reset_spaces(char **cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
			if (cmd[i][j] == -7)
				cmd[i][j] = SPACE;
	}
	return (cmd);
}

char	*reset_vars(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == -4)
			line[i] = DOLLAR;
	}
	return (line);
}

char	*reset_pipes(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == -1)
			line[i] = PIPE;
		else if (line[i] == -2)
			line[i] = LESS_THAN;
		else if (line[i] == -3)
			line[i] = MORE_THAN;
	}
	return (line);
}

char	*remove_quotes_metachar(int *i, int j, char *line, int quote)
{
	ft_memmove(&line[*i], &line[*i + 1], ft_strlen(&line[*i + 1]) + 1);
	if (*i)
		(*i)--;
	j--;
	while (++(*i) < j)
	{
		if (line[*i] == PIPE)
			line[*i] = -1;
		else if (line[*i] == LESS_THAN)
			line[*i] = -2;
		else if (line[*i] == MORE_THAN)
			line[*i] = -3;
		else if (line[*i] == DOLLAR && quote == SIMPLE_QUOTE)
			line[*i] = -4;
		else if (line[*i] == SPACE)
			line[*i] = -7;
	}
	ft_memmove(&line[j], &line[j + 1], ft_strlen(&line[j + 1]) + 1);
	*i = j - 1;
	return (line);
}
