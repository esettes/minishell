#include "../../inc/headers/minishell.h"

size_t	ft_split_len(char	**s)
{
	register size_t	len;

	len = 0;
	while (NULL != s[len])
		len++;
	return (len);
}

char	**ft_splitjoin(char **s1, char **s2)
{
	char	**aux;
	size_t	i;

	i = ft_split_len(s1) + ft_split_len(s2);
	aux = (char **) ft_calloc(i + 1, sizeof(char *));
	if (NULL == aux)
		return (aux);
	i = 0;
	while (NULL != s1[i])
	{
		aux[i] = s1[i];
		free (s1[i++]);
	}
	i = 0;
	while (NULL != s2[i])
	{
		aux[i] = s2[i];
		free (s2[i++]);
	}
	return (aux);
}
